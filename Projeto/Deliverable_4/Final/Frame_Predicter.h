#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include "Golomb_Encoder.hpp"

using namespace std;

class Frame_Predicter {
    //  Private variables
    private:
        Golomb_Encoder encoder;

        //  TODO FUNÇÃO DE PREVISÃO

    //  Public methods
    public:
        Frame_Predicter(Golomb_Encoder* newEncoder) {
            newEncoder = newEncoder;
        }

        int writeFrame(cv::Mat& frame) {
            int pixelValue = 0;
            int estimatedValue = 0; 
            int errorValue = 0; 

            //   For every row
            for (int i = 0; i < frame.rows; i++) {

                //  Reset the estimated value
                estimatedValue = 0;

                //  For every column
                for (int j = 0; j < frame.cols; j++) {
                    //  Extract monochrome value
                    pixelValue = (int) frame.at<uchar>(i,j);

                    //  Calculate the error value
                    errorValue = pixelValue - estimatedValue;

                    //  Update estimated with the last pixel value
                    estimatedValue = pixelValue;

                    //  Encode the pixels
                    encoder.encode(errorValue);
                }
            }
        }
}