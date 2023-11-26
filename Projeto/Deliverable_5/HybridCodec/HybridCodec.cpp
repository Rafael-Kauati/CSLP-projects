#ifndef HybridCodec_CPP
#define HybridCodec_CPP

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <cmath>
#include "../Golomb/Golomb.cpp"
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
    int numFrames;         /**< Number of frames in the video. */
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
     * This method writes the parameters for encoding to the BitStream object of the predictor and saves them in the HybridCodec object.
     * These params are wirtten in the BitStream as an header for the video file.
     *
     * @param newmParam The m parameter.
     * @param newxFrameSize The x-frame size.
     * @param newyFrameSize The y-frame size.
     * @param newfileType The file type index.
     * @param newnumFrames Number of frames in the video.
     * @param newfps Frames per second.
     * @param newblock_size Block size for encoding.
     * @param newsearch_area Search area size for encoding.
     * @param newintraframe_period Period between intra-frames.
     */
    void writeParams(int newmParam, int newxFrameSize, int newyFrameSize,
                     int newfileType, int newnumFrames = 1, int newfps = 1,
                     int newblock_size = 1, int newsearch_area = 1, int newintraframe_period = 1)
    {

        //  Save all the given params and give them to the predictor
        this->mParam = newmParam;
        this->fileType = newfileType;
        this->xFrameSize = newxFrameSize;
        this->yFrameSize = newyFrameSize;
        this->fps = newfps;
        this->numFrames = newnumFrames;
        this->block_size = newblock_size;
        this->search_area = newsearch_area;
        this->intraframe_period = newintraframe_period;

        p.writeParams(newmParam, newxFrameSize, newyFrameSize, newfileType, newnumFrames, newfps, newblock_size, newsearch_area, newintraframe_period);
    }

    /**
     * @brief Reads parameters from the BitStream and stores them in the HybridCodec object.
     *
     * This method reads the parameters from the BitStream and stores them in the HybridCodec object.
     * These params are read from the BitStream's header for the bin video file.
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
        //  Read the number of frames with 4 bytes (max: 2,147,483,647)
        this->numFrames = params[4];
        //  Read the FPS of the video with 1 byte (max: 255)
        this->fps = params[5];
        //  Read the block size of the video with 2 bytes (max: 65,535)
        this->block_size = params[6];
        //  Read the search area size of the video with 2 bytes (max: 65,535)
        this->search_area = params[7];
        //  Read the period between intraframes of the video with 1 byte (max: 255)
        this->intraframe_period = params[8];
    }

    /**
     * @brief Reads a video from the specified bin output file file using the Golomb decoder.
     * @param outputFile The path to the output video file.
     * @return A vector of frames from the video.
     */
    vector<cv::Mat> readVideo(string outputFile)
    {
        return p.readVideo(outputFile);
    }

    /**
     * @brief Writes a video to the BitStream using the specified VideoCapture object.
     * @param video The VideoCapture object containing the video to be written.
     */
    void writeVideo(cv::VideoCapture video)
    {
        p.writeVideo(video);
    }

    /**
     * @brief Closes the streams used by the predictor.
     */
    void close()
    {
        p.closeStreams();
    }

    /**
     * @brief Decodes a video and returns a vector of frames.
     * @param outputVidFile The path to the output video file.
     * @return A vector of frames from the decoded video.
     */
    vector<cv::Mat> decodeVideo(string outputVidFile)
    {
        int fileT = 0;

        //  Check the filetype (here MP4 is used for simplicity, but more can be added)
        if (this->fileType == 1)
        {
            fileT = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
        }

        Mat decodedFrame;
        Mat prevFrame;
        vector<cv::Mat> frameVector;

        //  Instanciate the video writer that will create the final mp4 file
        cv::VideoWriter decodedVideoWriter(outputVidFile, fileT, (double)this->fps, cv::Size(this->xFrameSize, this->yFrameSize), 1);

        //  Time the decoding
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;

        //  Loop through the video's frames
        for (int frameIndex = 0; frameIndex < this->numFrames; frameIndex++)
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

            //  Save the decoded frame inside a vector of frames and also add it to the final video
            frameVector.push_back(decodedFrame);
            decodedVideoWriter.write(decodedFrame);

            //  Stop the timer and print the time result
            end = std::chrono::steady_clock::now();
            cout << " -> Time for frame " << frameIndex + 1 << " : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";
        }

        //  Create the final video
        decodedVideoWriter.release();

        return frameVector;
    }

    /**
     * @brief Decodes a frame using the previous frame.
     * @param prevFrame The previous frame for inter-frame decoding.
     * @return The decoded frame.
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
     * @brief Decodes a channel using the previous channel.
     * @param prevChannel The previous channel for inter-channel decoding.
     * @return The decoded channel.
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
                Mat diff = p.decodeBlock(this->BLOCK_SIZE);

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
                        decodedFrame.at<uchar>(yd + y, xd + x) = (int)lastBlock.at<uchar>(yd, xd) + (int)diff.at<uchar>(yd, xd);
                    }
                }
            }
        }

        return decodedFrame;
    }

    /**
     * @brief Encodes a video using the specified VideoCapture object.
     * @param cap The VideoCapture object containing the video to be encoded.
     */
    void encodeVideo(cv::VideoCapture cap)
    {
        Mat frame;
        Mat prevFrame;

        //  Check if the video can be opened
        if (!cap.isOpened())
        {
            cout << "Error opening video stream or file" << endl;
            return;
        }

        //  Read the next frame
        cap >> frame;

        //  Time the encoding
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;

        //  Loop through the video's frames
        for (int frameIndex = 0; frameIndex < this->numFrames; frameIndex++)
        {

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

            //  Save the previous frame
            prevFrame = frame.clone();

            //  Read the next frame
            cap >> frame;

            //  Stop the timer and print the time result
            end = std::chrono::steady_clock::now();
            cout << " -> Time for frame " << frameIndex << " : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";
        }
    }

    /**
     * @brief Encodes a frame using the previous frame.
     * @param frame The current frame to be encoded.
     * @param prevFrame The previous frame for inter-frame encoding.
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
     * @param channel The current channel to be encoded.
     * @param prevChannel The previous channel for inter-channel encoding.
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
                Mat diff = cv::Mat::zeros(cv::Size(this->BLOCK_SIZE, this->BLOCK_SIZE), cv::IMREAD_GRAYSCALE);

                //  Get the best block's Mat
                Mat bestBlockMat = prevChannel(Rect(x + x_0, y + y_0, this->BLOCK_SIZE, this->BLOCK_SIZE));

                //  Calculate the difference between the current block and the best block
                //  Save the differene in a new diff block
                for (int yd = 0; yd < this->BLOCK_SIZE; yd++)
                {
                    for (int xd = 0; xd < this->BLOCK_SIZE; xd++)
                    {
                        diff.at<uchar>(yd, xd) = block.at<uchar>(yd, xd) - bestBlockMat.at<uchar>(yd, xd);
                    }
                }

                //  Save difference block
                p.encodeBlock(diff);

                //  Save the best block's offset
                p.encode(x_0);
                p.encode(y_0);
            }
        }
    }
};

#endif