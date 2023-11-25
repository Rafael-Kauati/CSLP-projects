#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include "Golomb_Encoder.hpp"
#include "Golomb_Decoder.hpp"

using namespace std;

class Frame_Predicter
{
    //  Private variables
private:
    Golomb_Encoder encoder;
    Golomb_Decoder decoder;
    int mParam;
    int xFrameSize;
    int yFrameSize;
    int fileType;
    int numFrames;
    int fps;

    //  Public methods
    public:
        Frame_Predicter();

        Frame_Predicter(string inputFile, string outputFile) : encoder(inputFile, outputFile), decoder(inputFile, outputFile) {
            mParam = 0;
            xFrameSize = 0;
            yFrameSize = 0;
            fileType = 0;
            fps = 0;
        }

        void closeStreams() {
            encoder.closeStreams();
        }

    void writeParams(int newmParam, int newxFrameSize, int newyFrameSize, int newfileType, int newnumFrames=1, int newfps=1) {
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


    void readParams() {
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

    void writeVideo(cv::VideoCapture video) {
        cv::Mat frame;
        bool read;
        int numFrame = 1;
        int maxFrames = (int)video.get(cv::CAP_PROP_FRAME_COUNT);
        
        //  For every frame 
        while (video.isOpened()) {
            read = video.read(frame);

            //  Last frame has been read
            if (!read) {
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

    vector<cv::Mat> readVideo(string outputFile) {
        int fileT;
        if (this->fileType == 1) {
            fileT = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
        }

        vector<cv::Mat> frameVector;

        cv::VideoWriter decodedVideoWriter(outputFile, fileT, (double)this->fps, cv::Size(this->xFrameSize, this->yFrameSize), 1);
        cv::Mat frame;

        for (int frameIndex = 0; frameIndex < this->numFrames; frameIndex++) {
            cout << " -> READING FRAME: " << frameIndex+1 << " of " << this->numFrames << "    \n";
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


    void writeFrameColour(cv::Mat &frame) { 
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

    cv::Mat readFrameColour() { 
        // Split the image into its Colour channels
        std::vector<cv::Mat> channels;
        cv::Mat ColourFrame;

        channels.push_back(readFrame());
        channels.push_back(readFrame());
        channels.push_back(readFrame());

        cv::merge(channels, ColourFrame);

        return ColourFrame;
    }

    void writeFrame(cv::Mat &frame) {
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

    cv::Mat readFrame() {
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
