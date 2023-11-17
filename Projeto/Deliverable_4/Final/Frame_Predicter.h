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

    //  Public methods
    public:
        Frame_Predicter();

        Frame_Predicter(string inputFile, string outputFile) : encoder(inputFile, outputFile), decoder(inputFile, outputFile) {
            mParam = 0;
            xFrameSize = 0;
            yFrameSize = 0;
            fileType = 0;
        }

        void closeStreams() {
            encoder.closeStreams();
        }

    void writeParams(int newmParam, int newxFrameSize, int newyFrameSize, int newfileType) {
        mParam = newmParam;
        xFrameSize = newxFrameSize;
        yFrameSize = newyFrameSize;
        fileType = newfileType;
        //  Write the m parameter with 1 byte (max: 255)
        encoder.writeInt(newmParam, 1);
        //  Write the x and y frame sizes with 2 bytes each (max: 65,535)
        encoder.writeInt(newxFrameSize, 2);
        encoder.writeInt(newyFrameSize, 2);
        //  Write the file format index with 1 byte (max: 255)
        encoder.writeInt(newfileType, 1);
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
        decoder.setMParam(this->mParam);
    }

    int writeFrame(cv::Mat &frame, int predictor=6) {
        int pixelValue = 0;
        int estimatedValue = 0;
        int errorValue = 0;

        cout << "\n";
        //   For every row
        for (int i = 0; i < yFrameSize; i++)
        {
            cout << "\e[A";
            cout << "\r";
            cout << " -> ENCODING ROW: " << i+1 << " of " << yFrameSize << "                    \n";
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

                //  Estimate the pixel value using the predictor
                switch (predictor) {
                case 1:
                    estimatedValue = a;
                    break;
                case 2:
                    estimatedValue = b;
                    break;
                case 3:
                    estimatedValue = c;
                    break;
                case 4:
                    estimatedValue = a + b - c;
                    break;
                case 5:
                    estimatedValue = a + (b - c) / 2;
                    break;
                case 6:
                    estimatedValue = b + (a - c) / 2;
                    break;
                case 7:
                    estimatedValue = (a + b) / 2;
                    break;
                case -1:
                    if (c >= max(a, b))
                    {
                        estimatedValue = min(a, b);
                    }
                    else if (c <= min(a, b))
                    {
                        estimatedValue = max(a, b);
                    }
                    else
                    {
                        estimatedValue = a + b - c;
                    }
                }

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

        return 0;
    }

    cv::Mat readFrame(int predictor=6) {
        int pixelValue = 0;
        int estimatedValue = 0;
        int errorValue = 0;

        cv::Mat frame = cv::Mat::zeros(cv::Size(xFrameSize, yFrameSize), cv::IMREAD_GRAYSCALE);
        cout << "\n";

        //   For every row
        for (int i = 0; i < this->yFrameSize; i++)
        {
            cout << "\e[A";
            cout << "\r";
            cout << " -> DECODING ROW: " << i+1 << " of " << yFrameSize << "                    \n";

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

                //  Estimate the pixel value using the predictor
                switch (predictor) {
                case 1:
                    estimatedValue = a;
                    break;
                case 2:
                    estimatedValue = b;
                    break;
                case 3:
                    estimatedValue = c;
                    break;
                case 4:
                    estimatedValue = a + b - c;
                    break;
                case 5:
                    estimatedValue = a + (b - c) / 2;
                    break;
                case 6:
                    estimatedValue = b + (a - c) / 2;
                    break;
                case 7:
                    estimatedValue = (a + b) / 2;
                    break;
                case -1:
                    if (c >= max(a, b))
                    {
                        estimatedValue = min(a, b);
                    }
                    else if (c <= min(a, b))
                    {
                        estimatedValue = max(a, b);
                    }
                    else
                    {
                        estimatedValue = a + b - c;
                    }
                }

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
