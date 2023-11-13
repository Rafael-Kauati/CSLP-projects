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

    //  Public methods
    public:
        Frame_Predicter();

        Frame_Predicter(Golomb_Encoder newEncoder, Golomb_Decoder newDecoder)  : encoder(newEncoder), decoder(newDecoder) {}

        void closeStreams() {
            encoder.closeStreams();
        }

    int writeFrame(cv::Mat &frame, int predictor=6) {
        int pixelValue = 0;
        int estimatedValue = 0;
        int errorValue = 0;

        //   For every row
        for (int i = 0; i < frame.rows; i++)
        {
            //  For every column
            for (int j = 0; j < frame.cols; j++)
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

    cv::Mat readFrame(int xFrameSize, int yFrameSize, int predictor=6) {
        int pixelValue = 0;
        int estimatedValue = 0;
        int errorValue = 0;

        cv::Mat frame = cv::Mat::zeros(cv::Size(xFrameSize, yFrameSize), CV_8UC1);

        //   For every row
        for (int i = 0; i < yFrameSize; i++)
        {
            cout << "DECODING ROW: " << i << " of " << yFrameSize << "                    \n";
            cout << "\e[A";
            cout << "\r";

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
                errorValue = decoder.decode();

                //  Calculate the error value
                pixelValue = errorValue + estimatedValue;

                //  Update estimated with the last pixel value
                estimatedValue = pixelValue;

                frame.at<uchar>(i, j) = (uchar)pixelValue;
            }
        }

        return frame;
    }
};
