#ifndef HybridCodec_CPP
#define HybridCodec_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <cmath>
#include "../Golomb/Golomb.cpp"
#include "../VideoReader/VideoReader.cpp"
#include "Frame_Predicter.h"
#include "BlockSearch.cpp"

using namespace std;
using namespace cv;

/**
 * @class HybridCodec
 * @brief Represents a hybrid video codec that combines intra-frame and inter-frame coding.
 *
 * The HybridCodec class provides functionalities for encoding and decoding video files using a combination of
 * intra-frame and inter-frame coding techniques. It supports customization through various parameters and utilizes
 * a BlockSearch mechanism for efficient inter-frame coding.
 */
class HybridCodec
{
private:
    string inputfile;      /**< Path to the input video file. */
    string outputfile;     /**< Path to the output video file. */
    int BLOCK_SIZE;        /**< Size of coding blocks. */
    int SEARCH_SIZE;       /**< Size of the search area for inter-frame coding. */
    int frequency;         /**< Frequency of intra-frame coding. */
    int mParam;            /**< The m parameter. */
    int fileType;          /**< File type index. */
    int xFrameSize;        /**< X-frame size. */
    int yFrameSize;        /**< Y-frame size. */
    int fps;               /**< Frames per second. */
    int block_size;        /**< Block size for encoding. */
    int search_area;       /**< Search area size for encoding. */
    int intraframe_period; /**< Period between intra-frames. */
    int SEARCH_STEP_SIZE;  /**< Step size for inter-frame coding. */

public:
    Frame_Predicter p; /**< Frame predictor object for intra-frame coding. */

    /**
     * @brief Constructor for the HybridCodec class.
     *
     * @param inputfile Path to the input video file.
     * @param outputfile Path to the output video file.
     * @param blockSize Size of coding blocks.
     * @param searchSize Size of the search area for inter-frame coding.
     * @param frequency Frequency of intra-frame coding.
     * @param stepSize Step size for inter-frame coding.
     */
    HybridCodec(string inputfile, string outputfile, int blockSize = 8, int searchSize = 8, int frequency = 6, int stepSize = 4)
        : p(inputfile, outputfile)
    {

        this->inputfile = inputfile;
        this->outputfile = outputfile;
        this->BLOCK_SIZE = blockSize;
        this->SEARCH_SIZE = searchSize;
        this->frequency = frequency;
        this->SEARCH_STEP_SIZE = stepSize;
    }

    /**
     * @brief Destructor for the HybridCodec class.
     */
    ~HybridCodec() {}

    /**
     * @brief Writes parameters for encoding to the predictor and saves them in the HybridCodec object.
     *
     * This method writes the parameters for encoding to the BitStream object of the predictor and saves them
     * in the HybridCodec object. These parameters are written in the BitStream as a header for the video file.
     *
     * @param newmParam The m parameter.
     * @param newxFrameSize The x-frame size.
     * @param newyFrameSize The y-frame size.
     * @param newfileType The file type index.
     * @param newfps Frames per second.
     * @param newblock_size Block size for encoding.
     * @param newsearch_area Search area size for encoding.
     * @param newintraframe_period Period between intra-frames.
     */

    void writeParams(int newmParam, int newxFrameSize, int newyFrameSize,
                     int newfileType, int newfps = 1,
                     int newblock_size = 1, int newsearch_area = 1, int newintraframe_period = 1)
    {

        //  Save all the given params and give them to the predictor
        this->mParam = newmParam;
        this->fileType = newfileType;
        this->xFrameSize = newxFrameSize;
        this->yFrameSize = newyFrameSize;
        this->fps = newfps;
        this->block_size = newblock_size;
        this->search_area = newsearch_area;
        this->intraframe_period = newintraframe_period;

        p.writeParams(newmParam, newxFrameSize, newyFrameSize, newfileType, newfps, newblock_size, newsearch_area, newintraframe_period);
    }

    /**
     * @brief Reads parameters from the BitStream and stores them in the HybridCodec object.
     *
     * This method reads the parameters from the BitStream and stores them in the HybridCodec object.
     * These parameters are read from the BitStream's header for the bin video file.
     */
    void readParams()
    {
        vector<int> params = p.readParams();

        //  Read the m parameter with 1 byte (max: 255)
        this->mParam = params[0];
        //  Read the x and y frame sizes with 2 bytes each (max: 65,535)
        this->xFrameSize = params[1];
        this->yFrameSize = params[2];
        //  Read the file format index with 1 byte (max: 255)
        this->fileType = params[3];
        //  Read the FPS of the video with 1 byte (max: 255)
        this->fps = params[4];
        //  Read the block size of the video with 2 bytes (max: 65,535)
        this->block_size = params[5];
        //  Read the search area size of the video with 2 bytes (max: 65,535)
        this->search_area = params[6];
        //  Read the period between intraframes of the video with 1 byte (max: 255)
        this->intraframe_period = params[7];
    }

    /**
     * @brief Closes the streams used by the predictor.
     *
     * This method closes the streams used by the predictor. It is responsible for closing any open streams, finalizing
     * any pending operations, and releasing associated resources.
     */
    void close()
    {
        p.closeStreams();
    }
    /**
     * @brief Decodes a video and returns a vector of frames.
     *
     * This method decodes a video using the specified output video file path. It utilizes intra-frame coding for frames
     * at the specified frequency and inter-frame coding for other frames. The decoded frames are saved in a vector, and
     * the final decoded video is written to the specified output video file.
     *
     * @param outputVidFile The path to the output video file.
     * @return A vector of frames from the decoded video.
     *
     * @note The video frames are decoded using intra-frame coding at a specified frequency and inter-frame coding for other frames.
     * @note The decoded frames are saved in a vector and added to the final video written to the specified output video file.
     * @note The timing information for each frame's decoding duration is printed to the console.
     * @note The frequency parameter determines the frames at which intra-frame coding is applied.
     */
    void decodeVideo(string outputVidFile, string outputYUVFile)
    {
        int fileT = 0;

        //  Check the filetype (here MP4 is used for simplicity, but more can be added)
        if (this->fileType == 1)
        {
            fileT = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
        }

        Mat decodedFrame;
        Mat prevFrame;

        //  Instanciate the video writer that will create the final mp4 file
        cv::VideoWriter decodedVideoWriter(outputVidFile, fileT, (double)this->fps, cv::Size(this->xFrameSize, this->yFrameSize), 1);

        //  Open the y4m file to write to
        ofstream outfile (outputYUVFile);           
        //  Write the y4m header
        outfile << "YUV4MPEG2 W" << this->xFrameSize << " H" << this->yFrameSize << " F" << this->fps << ":1 Ip A1:1 C444" << endl;

        //  Time the decoding
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;

        //  Loop through the video's frames
        for (int frameIndex = 0; !p.fileEnd(); frameIndex++)
        {

            //  Time the encoding
            begin = std::chrono::steady_clock::now();

            //  If is the frequency-th frame, decode the frame with intra-frame coding
            if (frameIndex % this->frequency == 0)
            {
                decodedFrame = p.readFrameColour();
            }
            else
            {
                decodedFrame = decodeFrame(prevFrame);
            }

            //  Save the previous frame
            prevFrame = decodedFrame.clone();

            if (p.fileEnd()) {
                break;
            }

            //  Save the decoded frame inside a vector of frames and also add it to the final video
            decodedVideoWriter.write(decodedFrame);
            
            outfile << "FRAME" << endl;

            for (int colour = 0; colour < 3; colour++) {
                for (int y = 0; y < this->yFrameSize; y++) {
                    for (int x = 0; x < this->xFrameSize; x++) {
                        outfile << decodedFrame.at<cv::Vec3b>(y, x)[colour];
                    }
                }
            }

            //  Stop the timer and print the time result
            end = std::chrono::steady_clock::now();
            cout << " -> Time for frame " << frameIndex + 1 << " : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";
        }

        //  Create the final video
        decodedVideoWriter.release();
        //  Close the output file
        outfile.close();

        return;
    }

    /**
     * @brief Decodes a frame using the previous frame for inter-frame decoding.
     *
     * This method decodes a frame by utilizing the previous frame for inter-frame decoding. It splits the previous frame
     * into its color channels, decodes each channel separately, and then merges the decoded channels to reconstruct the
     * final decoded frame.
     *
     * @param prevFrame The previous frame for inter-frame decoding.
     * @return The decoded frame.
     *
     * @note This method performs inter-frame decoding by utilizing the previous frame.
     * @note The previous frame is split into its color channels, and each channel is decoded separately.
     * @note The decoded channels are merged to reconstruct the final decoded frame.
     */
    Mat decodeFrame(Mat prevFrame)
    {
        std::vector<cv::Mat> channels;
        cv::Mat decodedFrame;

        //  Split the previous frame into channels
        vector<Mat> prevChannels;
        split(prevFrame, prevChannels);

        //  Decode each channel
        channels.push_back(decodeChannel(prevChannels[0]));
        channels.push_back(decodeChannel(prevChannels[1]));
        channels.push_back(decodeChannel(prevChannels[2]));

        //  Merge the current frame from the decoded channels
        cv::merge(channels, decodedFrame);

        return decodedFrame;
    }

    /**
     * @brief Decodes a channel using the previous channel for inter-channel decoding.
     *
     * This method decodes a channel using the previous channel for inter-channel decoding. It processes the channel in
     * blocks, decoding the difference block between the previous frame's block and the current block. It also decodes the
     * relative offset for the block's coordinates, retrieves the last block at the specified coordinates, and calculates
     * the decoded frame from the last block and the difference block.
     *
     * @param prevChannel The previous channel for inter-channel decoding.
     * @return The decoded channel.
     *
     * @note This method performs inter-channel decoding using the previous channel.
     * @note The channel is processed in blocks, and the difference block between the previous frame's block and the current
     * block is decoded.
     * @note The relative offset for the block's coordinates is decoded.
     * @note The last block is retrieved from the previous channel at the specified coordinates.
     * @note The decoded channel is calculated from the last block and the difference block.
     */
    Mat decodeChannel(Mat prevChannel)
    {
        //  Get the height and width of the channe
        int height = this->yFrameSize;
        int width = this->xFrameSize;

        cv::Mat decodedFrame = cv::Mat::zeros(cv::Size(width, height), cv::IMREAD_GRAYSCALE);

        //  Loop through the channel in blocks
        for (int y = 0; y < height; y += this->BLOCK_SIZE)
        {
            for (int x = 0; x < width; x += this->BLOCK_SIZE)
            {

                //  Get the difference block between the previous frame's block and the current block
                vector<vector<int>> diff = p.decodeBlock(this->BLOCK_SIZE);

                //  Get the best block's relative offset (for the coordinates)
                int xDiff = p.decode();
                int yDiff = p.decode();

                //  Get the last block at the defined coordinates
                Mat lastBlock = prevChannel(Rect(x + xDiff, y + yDiff, this->BLOCK_SIZE, this->BLOCK_SIZE));

                //  Calculate the decoded frame from the last block (bestBlock) + the difference block
                for (int yd = 0; yd < this->BLOCK_SIZE; yd++)
                {
                    for (int xd = 0; xd < this->BLOCK_SIZE; xd++)
                    {
                        decodedFrame.at<uchar>(yd + y, xd + x) = (int)lastBlock.at<uchar>(yd, xd) + diff.at(yd).at(xd);
                    }
                }
            }
        }

        return decodedFrame;
    }

    /**
     * @brief Encodes a video using the specified VideoCapture object.
     *
     * This method encodes a video using the specified VideoCapture object. It reads frames from the video, and for each
     * frame, it either encodes it with intra-frame coding if it is the frequency-th frame or with inter-frame coding
     * otherwise. The encoding process involves writing the frame to the BitStream, performing color channel splitting,
     * and encoding each channel separately.
     *
     * @param cap The VideoCapture object containing the video to be encoded.
     *
     * @note The video must be opened successfully using the VideoCapture object.
     * @note The encoding process involves reading frames, determining whether to use intra-frame or inter-frame coding,
     * writing frames to the BitStream, and encoding color channels separately.
     * @note For intra-frame coding, the frame is written directly to the BitStream using writeFrameColour.
     * @note For inter-frame coding, the frame is encoded using encodeFrame with the previous frame.
     * @note The time taken for encoding each frame is printed.
     */
    void encodeVideo(VideoReader& video) {
            
        int frameIndex = 0;
        Mat frame;
        Mat prevFrame;

        //  Check if the video can be opened
        if (video.readError()) {
            cout << "Error opening video stream or file" << endl;
            return;
        }

        //  Read the next frame
        frame = video.readNextYUVFrame();

        //  Time the encoding
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;

        //  Loop through the video's frames
        for (frameIndex = 0; !video.videoEnd(); frameIndex++) {

            //  Start the timer
            begin = std::chrono::steady_clock::now();

            //  If is the frequency-th frame, encode the frame with intra-frame coding
            if (frameIndex % this->frequency == 0)
            {
                p.writeFrameColour(frame);
            }
            //  Else, encode the frame with inter-frame coding
            else
            {
                encodeFrame(frame, prevFrame);
            }

            //  Copy the previous frame
            prevFrame = frame.clone();

            //  Read the next frame
            frame = video.readNextYUVFrame();

            //  Stop the timer and print the time result
            end = std::chrono::steady_clock::now();
            cout << " -> Time for frame " << frameIndex + 1 << " : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";
        }
    }

    /**
     * @brief Encodes a frame using the previous frame.
     *
     * This method encodes a frame using the previous frame for inter-frame encoding. It operates on each color channel
     * separately, encoding the differences between the current frame and the previous frame in each channel.
     *
     * @param frame The current frame to be encoded.
     * @param prevFrame The previous frame for inter-frame encoding.
     *
     * @note The method splits the frames into color channels and then encodes the differences between the corresponding
     * channels of the current frame and the previous frame.
     * @note The encoding process involves encoding each color channel using the encodeChannel method.
     */
    void encodeFrame(Mat frame, Mat prevFrame)
    {
        //  Split the current frame into channels
        vector<Mat> channels;
        split(frame, channels);

        //  Split the previous frame into channels
        vector<Mat> prevChannels;
        split(prevFrame, prevChannels);

        //  Encode each channel
        encodeChannel(channels[0], prevChannels[0]);
        encodeChannel(channels[1], prevChannels[1]);
        encodeChannel(channels[2], prevChannels[2]);
    }

    /**
     * @brief Encodes a channel using the previous channel.
     *
     * This method encodes a channel using the previous channel for inter-channel encoding. It operates on blocks within
     * the channel, finding the best matching block in the previous channel, calculating the difference between the current
     * block and the best block, and encoding the difference block along with the relative offset of the best block.
     *
     * @param channel The current channel to be encoded.
     * @param prevChannel The previous channel for inter-channel encoding.
     *
     * @note The encoding process involves dividing the channel into blocks, finding the best matching block in the
     * previous channel, and encoding the difference block along with the relative offset of the best block.
     * @note The BlockSearch entity is used to find the best block position in the previous channel.
     * @note The difference block is calculated as the element-wise difference between the current block and the best block.
     * @note The encoded difference block and the relative offset of the best block are saved using the BitStream.
     */
    void encodeChannel(Mat channel, Mat prevChannel)
    {
        //  Get the height and width of the channel
        int height = this->yFrameSize;
        int width = this->xFrameSize;

        //  Create the block search entity
        BlockSearch bSearch = BlockSearch(this->BLOCK_SIZE, this->SEARCH_SIZE, this->SEARCH_STEP_SIZE);

        //  Loop through the channel in blocks
        for (int y = 0; y < height; y += this->BLOCK_SIZE)
        {
            for (int x = 0; x < width; x += this->BLOCK_SIZE)
            {

                //  Get the current block Mat
                Mat block = channel(Rect(x, y, this->BLOCK_SIZE, this->BLOCK_SIZE));

                //  Find the position of the best block close to us
                vector<double> bestBlock = bSearch.findBestBlock(prevChannel, block, x, y);

                //  Get the best block's relative offset (for the coordinates)
                int x_0 = (int)bestBlock[0];
                int y_0 = (int)bestBlock[1];

                //  Create a Mat for the difference block between the previous frame's block and the current block
                //Mat diff = cv::Mat::zeros(cv::Size(this->BLOCK_SIZE, this->BLOCK_SIZE), cv::IMREAD_GRAYSCALE);
                vector<vector<int>> diff (this->BLOCK_SIZE);

                //  Get the best block's Mat
                Mat bestBlockMat = prevChannel(Rect(x + x_0, y + y_0, this->BLOCK_SIZE, this->BLOCK_SIZE));

                //  Calculate the difference between the current block and the best block
                //  Save the differene in a new diff block
                for (int yd = 0; yd < this->BLOCK_SIZE; yd++) {                        
                    diff[yd] = vector<int>(this->BLOCK_SIZE); 

                    for (int xd = 0; xd < this->BLOCK_SIZE; xd++) {
                        diff[yd][xd] = (int)block.at<uchar>(yd, xd) - (int)bestBlockMat.at<uchar>(yd, xd);
                    }
                }


                //  Save difference block
                p.encodeBlock(diff, this->BLOCK_SIZE);

                //  Save the best block's offset
                p.encode(x_0);
                p.encode(y_0);
            }
        }
    }
};

#endif