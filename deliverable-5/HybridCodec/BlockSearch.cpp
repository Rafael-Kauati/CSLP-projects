#ifndef BlockSearch_CPP
#define BlockSearch_CPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;

class BlockSearch
{
private:
    int BLOCK_SIZE;
    int SEARCH_SIZE;
    int STEP_SIZE;

    // Returns the mean squared error between two blocks
    double MSE(Mat& A, Mat& B) {
        double sum = 0.0;

        for(int i = 0; i < A.rows; i++) {
            for(int j = 0; j < A.cols; j++) {
                sum += pow(A.at<uchar>(i,j) - B.at<uchar>(i,j), 2);
            }
        }

        return sum / (A.rows * A.cols);
    }
    
public:// Constructor: Sets the block size and search area size
    BlockSearch(int blockSize, int searchSize, int stepSize=2) {
        this->BLOCK_SIZE = blockSize;
        this->SEARCH_SIZE = searchSize;
        this->STEP_SIZE = stepSize;
    };

    ~BlockSearch(){};

    vector<double> findBestBlock(Mat &prevFrame, Mat &block, int x_0, int y_0) {
        double minMSE = -1;

        double dx = 0;
        double dy = 0;

        // Define the search area
        int startX = max(0, x_0 - this->SEARCH_SIZE);
        int startY = max(0, y_0 - this->SEARCH_SIZE);
        int endX = min(prevFrame.cols - this->BLOCK_SIZE, x_0 + this->SEARCH_SIZE);
        int endY = min(prevFrame.rows - this->BLOCK_SIZE, y_0 + this->SEARCH_SIZE);

        // Search for the best block
        for(int j = startY; j < endY; j += this->STEP_SIZE) {
            for(int i = startX; i < endX; i += this->STEP_SIZE) {   

                // Get the block
                Mat searchBlock = prevFrame(Rect(i, j, this->BLOCK_SIZE, this->BLOCK_SIZE));

                // Calculate the MSE
                double mse = MSE(block, searchBlock);

                // Update the best block if the MSE is better than the previous best
                if(mse < minMSE || minMSE == -1) {
                    minMSE = mse;
                    dx = i - x_0;
                    dy = j - y_0;
                }
            }
        }

        return vector<double> {dx, dy};
    }
};

#endif

