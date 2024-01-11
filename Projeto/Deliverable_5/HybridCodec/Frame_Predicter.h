#ifndef Frame_Predicter_HPP
#define Frame_Predicter_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include "../Golomb/Golomb_Encoder.hpp"
#include "../Golomb/Golomb_Decoder.hpp"

using namespace std;

/**
 * @class Frame_Predicter
 * @brief Manages the prediction, encoding, and decoding of video frames using Golomb encoding.
 *
 * The Frame_Predicter class encapsulates functionality for predicting, encoding, and decoding
 * video frames using Golomb encoding. It utilizes Golomb_Encoder and Golomb_Decoder for the
 * compression and decompression process, respectively.
 */
class Frame_Predicter
{
    //  Private variables
private:
    Golomb_Encoder encoder; ///< Golomb Encoder object for encoding pixel values.
    Golomb_Decoder decoder; ///< Golomb Decoder object for decoding encoded pixel values.
    int mParam;             ///< Parameter 'm' for Golomb encoding.
    int xFrameSize;         ///< Width of the frame.
    int yFrameSize;         ///< Height of the frame.
    int fileType;           ///< File format index.
    int numFrames;          ///< Number of frames in the video.
    int fps;                ///< Frames per second of the video.
    int block_size;         ///< Block size for encoding and decoding.
    int search_area;        ///< Search area size for prediction.
    int intraframe_period;  ///< Period between intraframes in the video.

    //  Public methods
public:
    /**
     * @brief Default constructor for the Frame_Predicter class.
     */
    Frame_Predicter();

    /**
     * @brief Parameterized constructor for the Frame_Predicter class.
     *
     * Initializes the Frame_Predicter object with the given input and output video file paths.
     *
     * @param inputFile Path to the input video file for encoding and decoding.
     * @param outputFile Path to the output video file for encoding.
     */
    Frame_Predicter(string inputFile, string outputFile) : encoder(inputFile, outputFile), decoder(inputFile, outputFile)
    {
        mParam = 0;
        xFrameSize = 0;
        yFrameSize = 0;
        fileType = 0;
        fps = 0;
        block_size = 0;
        search_area = 0;
        intraframe_period = 0;
    }

    /**
     * @brief Closes the associated Golomb encoder streams.
     *
     * This method closes the Golomb encoder streams to ensure proper cleanup
     * and resource management after video frame processing.
     */
    void closeStreams()
    {
        encoder.closeStreams();
    }

    /**
     * @brief Writes the parameters for the video encoding and decoding.
     *
     * This method sets the parameters for video encoding and decoding, including Golomb encoding
     * parameter 'm', frame dimensions, file type, number of frames, frames per second (FPS),
     * block size, search area size, and intraframe period. It then writes these parameters to the
     * output file using Golomb encoding.
     *
     * @param newmParam Golomb encoding parameter 'm'.
     * @param newxFrameSize Width of the frame.
     * @param newyFrameSize Height of the frame.
     * @param newfileType File format index.
     * @param newnumFrames Number of frames in the video.
     * @param newfps Frames per second of the video.
     * @param newblock_size Block size for encoding and decoding.
     * @param newsearch_area Search area size for prediction.
     * @param newintraframe_period Period between intraframes in the video.
     */
    void writeParams(int newmParam, int newxFrameSize, int newyFrameSize, int newfileType, int newnumFrames = 1, int newfps = 1, int newblock_size = 1, int newsearch_area = 1, int newintraframe_period = 1)
    {
        mParam = newmParam;
        xFrameSize = newxFrameSize;
        yFrameSize = newyFrameSize;
        fileType = newfileType;
        numFrames = newnumFrames;
        fps = newfps;
        block_size = newblock_size;
        search_area = newsearch_area;
        intraframe_period = newintraframe_period;

        //  Write the m parameter with 1 byte (max: 255)
        encoder.writeInt(newmParam, 1);
        //  Write the x and y frame sizes with 2 bytes each (max: 65,535)
        encoder.writeInt(newxFrameSize, 2);
        encoder.writeInt(newyFrameSize, 2);
        //  Write the file format index with 1 byte (max: 255)
        encoder.writeInt(newfileType, 1);
        //  Write the number of frames with 4 bytes (max: 2,147,483,647)
        encoder.writeInt(newnumFrames, 4);
        //  Write the FPS of the video with 1 byte (max: 255)
        encoder.writeInt(newfps, 1);
        //  Write the block size of the video with 2 bytes (max: 65,535)
        encoder.writeInt(newblock_size, 2);
        //  Write the search area size of the video 2 bytes (max: 65,535)
        encoder.writeInt(newsearch_area, 2);
        //  Write the period between intraframes of the video with 1 byte (max: 255)
        encoder.writeInt(newintraframe_period, 1);

        encoder.setMParam(newmParam);
    }

    /**
     * @brief Reads the parameters for the video encoding and decoding.
     *
     * This method reads the parameters for video encoding and decoding, including Golomb encoding
     * parameter 'm', frame dimensions, file type, number of frames, frames per second (FPS),
     * block size, search area size, and intraframe period. It then sets these parameters for further use.
     * These params are read from the encoded file's header.
     *
     * @return A vector containing the read parameters in the following order:
     *         [mParam, xFrameSize, yFrameSize, fileType, numFrames, fps, block_size, search_area, intraframe_period].
     *
     */
    vector<int> readParams()
    {
        //  Read the m parameter with 1 byte (max: 255)
        this->mParam = decoder.readInt(1);
        //  Read the x and y frame sizes with 2 bytes each (max: 65,535)
        this->xFrameSize = decoder.readInt(2);
        this->yFrameSize = decoder.readInt(2);
        //  Read the file format index with 1 byte (max: 255)
        this->fileType = decoder.readInt(1);
        //  Read the number of frames with 4 bytes (max: 2,147,483,647)
        this->numFrames = decoder.readInt(4);
        //  Read the FPS of the video with 1 byte (max: 255)
        this->fps = decoder.readInt(1);
        //  Read the block size of the video with 2 bytes (max: 65,535)
        this->block_size = decoder.readInt(2);
        //  Read the search area size of the video with 2 bytes (max: 65,535)
        this->search_area = decoder.readInt(2);
        //  Read the period between intraframes of the video with 1 byte (max: 255)
        this->intraframe_period = decoder.readInt(1);

        decoder.setMParam(this->mParam);

        return vector<int>{this->mParam, this->xFrameSize, this->yFrameSize, this->fileType, this->numFrames,
                           this->fps, this->block_size, this->search_area, this->intraframe_period};
    }

    /**
     * @brief Writes video frames to the Golomb encoded file.
     *
     * This method reads frames from the given video capture and writes Golomb encoded versions of
     * each frame to the Golomb encoded file. It displays progress information while writing frames.
     *
     * @param video The video capture object.
     */
    void writeVideo(cv::VideoCapture video)
    {
        cv::Mat frame;
        bool read;
        int numFrame = 1;
        int maxFrames = (int)video.get(cv::CAP_PROP_FRAME_COUNT);

        //  For every frame
        while (video.isOpened())
        {
            read = video.read(frame);

            //  Last frame has been read
            if (!read)
            {
                break;
            }

            cout << " -> WRITING FRAME: " << numFrame << " of " << this->numFrames << "    \n";
            cout << "\e[A";
            cout << "\r";

            //  Write the frame
            this->writeFrameColour(frame);

            numFrame++;
        }

        cout << "\n";
    }

    /**
     * @brief Reads the parameters for the video encoding and decoding.
     *
     * This method reads the parameters for video encoding and decoding, including Golomb encoding
     * parameter 'm', frame dimensions, file type, number of frames, frames per second (FPS),
     * block size, search area size, and intraframe period. It then sets these parameters for further use.
     *
     * @return A vector containing the read parameters in the following order:
     *         [mParam, xFrameSize, yFrameSize, fileType, numFrames, fps, block_size, search_area, intraframe_period].
     */
    vector<cv::Mat> readVideo(string outputFile)
    {
        int fileT;
        if (this->fileType == 1)
        {
            fileT = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
        }

        vector<cv::Mat> frameVector;

        cv::VideoWriter decodedVideoWriter(outputFile, fileT, (double)this->fps, cv::Size(this->xFrameSize, this->yFrameSize), 1);
        cv::Mat frame;

        for (int frameIndex = 0; frameIndex < this->numFrames; frameIndex++)
        {
            cout << " -> READING FRAME: " << frameIndex + 1 << " of " << this->numFrames << "    \n";
            cout << "\e[A";
            cout << "\r";

            frame = readFrameColour();

            frameVector.push_back(frame);

            decodedVideoWriter.write(frame);
        }
        decodedVideoWriter.release();

        cout << "\n";

        return frameVector;
    }

    /**
     * @brief Writes a color frame by encoding separate color channels.
     *
     * This method takes a color frame, splits it into individual color channels,
     * and encodes each channel separately using Golomb encoding. The resulting Golomb
     * encoded frames are then written to the output stream.
     *
     * @param frame The input color frame in YUV format.
     *
     * @note This method is originaly a helper method for writeVideo(). As the writeVideo()
     *       method accepts a cv::VideoCapture object, the channels are automatically converted to
     *       RGB format, despite the input frame being in YUV format.
     */
    void writeFrameColour(cv::Mat &frame)
    {
        // Split the image into its Colour channels
        std::vector<cv::Mat> channels;
        cv::split(frame, channels);

        cv::Mat VChannel = channels[0];
        cv::Mat UChannel = channels[1];
        cv::Mat YChannel = channels[2];

        writeFrame(VChannel);
        writeFrame(UChannel);
        writeFrame(YChannel);
    }

    /**
     * @brief Reads a color frame by decoding separate color channels.
     *
     * This method reads Golomb encoded frames for individual color channels,
     * decodes each channel separately using Golomb decoding, and then merges them to
     * reconstruct the original color frame.
     *
     * @return The reconstructed color frame.
     */
    cv::Mat readFrameColour()
    {
        // Split the image into its Colour channels
        std::vector<cv::Mat> channels;
        cv::Mat ColourFrame;

        channels.push_back(readFrame());
        channels.push_back(readFrame());
        channels.push_back(readFrame());

        cv::merge(channels, ColourFrame);

        return ColourFrame;
    }

    /**
     * @brief Writes a frame by encoding pixel values using Golomb encoding.
     *
     * This method encodes a frame by calculating the prediction error for each pixel
     * based on the previously encoded pixels in the frame. The prediction error is
     * then encoded using Golomb encoding and written to the output stream.
     *
     * @param frame The input frame to be encoded.
     *
     * @note The Golomb encoding is used to compress the prediction error of each pixel.
     *       The encoding process involves estimating pixel values, calculating prediction
     *       errors, and updating the prediction for subsequent pixels.
     *       We are using JPEG-6's prediction algorithm, which is based on the
     *       formula: a + (b - c) / 2, because is the most balanced one.
     */
    void writeFrame(cv::Mat &frame)
    {
        int pixelValue = 0;
        int estimatedValue = 0;
        int errorValue = 0;

        //   For every row
        for (int i = 0; i < yFrameSize; i++)
        {
            //  For every column
            for (int j = 0; j < xFrameSize; j++)
            {
                int a, b, c;
                if (i == 0 && j == 0)
                {
                    a = 0;
                    b = 0;
                    c = 0;
                }
                else if (i == 0)
                {
                    a = 0;
                    b = (int)frame.at<uchar>(i, j - 1);
                    c = 0;
                }
                else if (j == 0)
                {
                    a = (int)frame.at<uchar>(i - 1, j);
                    b = 0;
                    c = 0;
                }
                else
                {
                    a = (int)frame.at<uchar>(i, j - 1);
                    b = (int)frame.at<uchar>(i - 1, j);
                    c = (int)frame.at<uchar>(i - 1, j - 1);
                }

                estimatedValue = b + (a - c) / 2;

                //  Extract monochrome value
                pixelValue = (int)frame.at<uchar>(i, j);

                //  Calculate the error value
                errorValue = pixelValue - estimatedValue;

                //  Update estimated with the last pixel value
                estimatedValue = pixelValue;

                //  Encode the pixels
                encoder.encode(errorValue);
            }
        }

        return;
    }

    /**
     * @brief Reads and reconstructs a frame using Golomb decoding.
     *
     * This method reads the Golomb-encoded prediction errors from the input stream,
     * reconstructs the pixel values, and assembles them into a frame using Golomb decoding.
     * The Golomb decoding algorithm is applied to reconstruct the entire frame based on
     * the encoded prediction errors for each pixel.
     *
     * @return The reconstructed frame as a cv::Mat.
     *
     * @note The Golomb decoding process involves reading the encoded prediction errors,
     *       reconstructing the pixel values, and assembling them into a cv::Mat frame.
     *       The decoding process is applied to each pixel of the frame to reconstruct the
     *       original pixel values.
     *       We are using JPEG-6's prediction algorithm, which is based on the
     *       formula: a + (b - c) / 2, because is the most balanced one.
     */
    cv::Mat readFrame()
    {
        int pixelValue = 0;
        int estimatedValue = 0;
        int errorValue = 0;

        cv::Mat frame = cv::Mat::zeros(cv::Size(xFrameSize, yFrameSize), cv::IMREAD_GRAYSCALE);

        //   For every row
        for (int i = 0; i < this->yFrameSize; i++)
        {
            //  For every column
            for (int j = 0; j < this->xFrameSize; j++)
            {
                int a, b, c;
                if (i == 0 && j == 0)
                {
                    a = 0;
                    b = 0;
                    c = 0;
                }
                else if (i == 0)
                {
                    a = 0;
                    b = (int)frame.at<uchar>(i, j - 1);
                    c = 0;
                }
                else if (j == 0)
                {
                    a = (int)frame.at<uchar>(i - 1, j);
                    b = 0;
                    c = 0;
                }
                else
                {
                    a = (int)frame.at<uchar>(i, j - 1);
                    b = (int)frame.at<uchar>(i - 1, j);
                    c = (int)frame.at<uchar>(i - 1, j - 1);
                }

                estimatedValue = b + (a - c) / 2;

                //  Extract monochrome value
                errorValue = decoder.decode();

                //  Calculate the error value
                pixelValue = errorValue + estimatedValue;

                //  Update estimated with the last pixel value
                estimatedValue = pixelValue;

                frame.at<uchar>(i, j) = pixelValue;
            }
        }

        return frame;
    }

    /**
     * @brief Decodes a block of pixels using Golomb decoding.
     *
     * This method decodes a block of pixels from the input stream using Golomb decoding.
     * The Golomb decoding algorithm is applied to reconstruct the pixel values based on
     * the encoded prediction errors.
     *
     * @param block_size The size of the block to be decoded.
     * @return The decoded block as a cv::Mat.
     */
    cv::Mat decodeBlock(int block_size)
    {
        return decoder.decodeBlock(block_size);
    }

    /**
     * @brief Encodes a block of pixel values using Golomb encoding.
     *
     * This method takes a block of pixel values as a cv::Mat and applies Golomb encoding
     * to compress the block. The Golomb encoding algorithm is utilized to represent the
     * prediction errors between the pixels of the block, resulting in a compressed
     * representation of the pixel values.
     *
     * @param block The block of pixel values to be encoded.
     */
    void encodeBlock(cv::Mat block)
    {
        encoder.encodeBlock(block);
    }

    /**
     * @brief Decodes and retrieves a single integer value using Golomb decoding.
     *
     * This method applies Golomb decoding to retrieve a single integer value
     * from the encoded bitstream. The Golomb decoding algorithm is utilized
     * to reconstruct the original integer value that was encoded using Golomb encoding.
     *
     * @return The decoded integer value.
     */
    int decode()
    {
        return decoder.decode();
    }

    /**
     * @brief Encodes and compresses a single integer value using Golomb encoding.
     *
     * This method applies Golomb encoding to compress a given integer value and
     * writes the encoded bits to the output bitstream. Golomb encoding is utilized
     * to represent the integer value in a more compact form for compression purposes.
     *
     * @param num The integer value to be encoded and compressed.
     */
    void encode(int num)
    {
        encoder.encode(num);
    }
};

#endif