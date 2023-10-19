#include <iostream>
#include <string>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

/**
 * @brief A class to copy an image pixel by pixel.
 * It is a simple program to copy an image pixel by pixel.
 * It takes an input image (inpImg.jpg) and creates a blank blank image (outImg.jpg) with the same pixel width and height.
 * Then, it copies the pixels from the input image to the blank image and writes it to the output file.
 * 
 * @return 0 if successful, -1 otherwise
 */

int main()
{

    //  Input and Output files
    std::string inpFilename = "inpImg.jpg";
    std::string outFilename = "outImg.jpg"; 

    Vec3b value;

    Mat input = imread(inpFilename, IMREAD_COLOR);
    Mat output(input.rows, input.cols, CV_8UC3, Scalar(10, 100, 150));

    std::cout << " Copying file " << inpFilename << " to " << outFilename << ".\n";

    // For each pixel in the input image, copy it to the output image
    for (int col = 0; col < input.cols; col++)
    {
        for (int row = 0; row < input.rows; row++)
        {
            value = input.at<Vec3b>(row, col);
            output.at<Vec3b>(row, col) = value;
        }
    }

    imwrite(outFilename, output);

    return 0;
}