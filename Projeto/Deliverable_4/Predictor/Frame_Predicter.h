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
 *
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
    Golomb_Encoder encoder; ///< Golomb encoder for video frame compression.
    Golomb_Decoder decoder; ///< Golomb decoder for video frame decompression.
    int mParam;             ///< Parameter 'm' used in Golomb encoding and decoding.
    int xFrameSize;         ///< Width of video frames.
    int yFrameSize;         ///< Height of video frames.
    int fileType;           ///< Index representing the file format of the video.
    int numFrames;          ///< Total number of frames in the video.
    int fps;                ///< Frames per second of the video.

    //  Public methods
public:
    /**
     * @brief Default constructor for the Frame_Predicter class.
     */
    Frame_Predicter();

    /**
     * @brief Constructor for the Frame_Predicter class with input and output file names.
     *
     * Initializes a Frame_Predicter object with the provided input and output file names.
     *
     * @param inputFile The name of the input file.
     * @param outputFile The name of the output file.
     */
    Frame_Predicter(string inputFile, string outputFile) : encoder(inputFile, outputFile), decoder(inputFile, outputFile)
    {
        mParam = 0;
        xFrameSize = 0;
        yFrameSize = 0;
        fileType = 0;
        fps = 0;
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
     * @brief Writes video parameters to the Golomb encoder stream.
     *
     * Writes video parameters such as 'm', frame sizes, file type, number of frames,
     * and frames per second to the Golomb encoder stream.
     * These params are written to the start of the encoded file to form a header.
     *
     * @param newmParam The value of parameter 'm' for Golomb encoding.
     * @param newxFrameSize Width of video frames.
     * @param newyFrameSize Height of video frames.
     * @param newfileType Index representing the file format of the video.
     * @param newnumFrames Total number of frames in the video (default: 1).
     * @param newfps Frames per second of the video (default: 1).
     */
    void writeParams(int newmParam, int newxFrameSize, int newyFrameSize, int newfileType, int newnumFrames = 1, int newfps = 1)
    {
        mParam = newmParam;
        xFrameSize = newxFrameSize;
        yFrameSize = newyFrameSize;
        fileType = newfileType;
        numFrames = newnumFrames;
        fps = newfps;
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

        encoder.setMParam(newmParam);
    }

    /**
     * @brief Reads video parameters from the Golomb decoder stream.
     *
     * Reads video parameters such as 'm', frame sizes, file type, number of frames,
     * and frames per second from the Golomb decoder stream.
     * These params are read from the encoded file's header.
     */
    void readParams()
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

        decoder.setMParam(this->mParam);
    }

    /**
     * @brief Writes video frames to the Golomb encoder stream.
     *
     * Reads frames from a given video capture object and writes them to the Golomb encoder stream.
     *
     * @param video A cv::VideoCapture object representing the input video.
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
     * @brief Reads video frames from the Golomb decoder stream.
     *
     * Reads video frames from the Golomb decoder stream and returns them as a vector of cv::Mat objects.
     *
     * @param outputFile The name of the output file for writing the decoded video.
     * @return A vector containing decoded video frames.
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
     * @brief Writes a color video frame to the Golomb encoder stream.
     *
     * Splits the input frame into color channels and writes them to the Golomb encoder stream.
     *
     * @note This method is originaly a helper method for writeVideo(). As the writeVideo() method accepts a cv::VideoCapture object, the channels are automatically converted to RGB format, despite the input frame being in YUV format.
     *
     * @param frame The input color video frame.
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
     * @brief Reads a color video frame from the Golomb decoder stream.
     *
     * Reads color video channels from the Golomb decoder stream and merges them into a single cv::Mat object.
     *
     * @return A cv::Mat object containing the decoded color video frame.
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
     * @brief Writes a video frame to the Golomb encoder stream.
     *
     * Encodes a monochrome video frame/ video frame channel using Golomb encoding and writes it to the Golomb encoder stream.
     *
     * @param frame The input monochrome video frame/ video frame channel.
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
     * @brief Reads a video frame from the Golomb decoder stream.
     *
     * Decodes a monochrome video frame/ video frame channel from the Golomb decoder stream and returns it as a cv::Mat object.
     *
     * @return A cv::Mat object containing the decoded monochrome video frame/ video frame channel.
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
};
