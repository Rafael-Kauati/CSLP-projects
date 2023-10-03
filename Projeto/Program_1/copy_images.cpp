#include <iostream>
#include <string>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

int main() {

    //  Input and Output files
    std::string inpFilename = "inpImg.jpg";
    std::string outFilename = "outImg.jpg";

    Vec3b value;
    
    //  Load input image object, create the output with the same pixel width and height
    Mat input = imread(inpFilename, IMREAD_COLOR);
    Mat output(input.rows, input.cols, CV_8UC3, Scalar(10, 100, 150));
    
    std::cout << " Copying file " << inpFilename << " to " << outFilename << ".\n";

    //  For every pixel column and row, copy to the blank image
    for (int col = 0; col < input.cols; col++){
        for (int row = 0; row < input.rows; row++){
                value = input.at<Vec3b>(row,col);
                output.at<Vec3b>(row, col) = value;
        }
    }

    //  Write the blank image to the output file
    imwrite(outFilename, output);

    return 0;
}