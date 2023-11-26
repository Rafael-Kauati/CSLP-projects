#ifndef BlockSearch_CPP
#define BlockSearch_CPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;

/**
 * @class BlockSearch
 * @brief Performs block-based motion estimation to find the best matching block in a given search area.
 *
 * The BlockSearch class calculates the Mean Squared Error (MSE) between a target block and blocks within a specified
 * search area. It returns the displacement vector (dx, dy) representing the best-matching block's offset.
 */
class BlockSearch
{
private:
    int BLOCK_SIZE;  ///< Size of the target block
    int SEARCH_SIZE; ///< Size of the search area around the target block
    int STEP_SIZE;   ///< Step size for the search within the search area

    /**
     * @brief Calculates the Mean Squared Error (MSE) between two blocks.
     *
     * @param A The first block.
     * @param B The second block.
     * @return The MSE between the two blocks.
     */
    double MSE(Mat &A, Mat &B)
    {
        double sum = 0.0;

        for (int i = 0; i < A.rows; i++)
        {
            for (int j = 0; j < A.cols; j++)
            {
                sum += pow(A.at<uchar>(i, j) - B.at<uchar>(i, j), 2);
            }
        }

        return sum / (A.rows * A.cols);
    }

public: // Constructor: Sets the block size and search area size
    /**
     * @brief Constructor for the BlockSearch class.
     *
     * @param blockSize Size of the target block.
     * @param searchSize Size of the search area around the target block.
     * @param stepSize Step size for the search within the search area.
     */
    BlockSearch(int blockSize, int searchSize, int stepSize = 2)
    {
        this->BLOCK_SIZE = blockSize;
        this->SEARCH_SIZE = searchSize;
        this->STEP_SIZE = stepSize;
    };

    /**
     * @brief Destructor for the BlockSearch class.
     */
    ~BlockSearch(){};

    /**
     * @brief Finds the best-matching block in a specified search area for a given target block.
     * 
     * The search area is defined by the previous frame and the target block is defined by the current frame.
     * This function uses an exhaustive search to find the best-matching block in the search area.
     * 
     * Because of time constraints, this function is not as efficient as it could be. It is possible to
     * use a more efficient search algorithm such as the three-step search algorithm or the diamond search algorithm.
     *
     * @param prevFrame The previous frame containing the search area.
     * @param block The target block for motion estimation.
     * @param x_0 The x-coordinate of the target block in the frame.
     * @param y_0 The y-coordinate of the target block in the frame.
     * @return A vector representing the displacement (dx, dy) of the best-matching block.
     */
    vector<double> findBestBlock(Mat &prevFrame, Mat &block, int x_0, int y_0)
    {
        double minMSE = -1;

        double dx = 0;
        double dy = 0;

        // Define the search area
        int startX = max(0, x_0 - this->SEARCH_SIZE);
        int startY = max(0, y_0 - this->SEARCH_SIZE);
        int endX = min(prevFrame.cols - this->BLOCK_SIZE, x_0 + this->SEARCH_SIZE);
        int endY = min(prevFrame.rows - this->BLOCK_SIZE, y_0 + this->SEARCH_SIZE);

        // Search for the best block
        for (int j = startY; j < endY; j += this->STEP_SIZE)
        {
            for (int i = startX; i < endX; i += this->STEP_SIZE)
            {

                // Get the block
                Mat searchBlock = prevFrame(Rect(i, j, this->BLOCK_SIZE, this->BLOCK_SIZE));

                // Calculate the MSE
                double mse = MSE(block, searchBlock);

                // Update the best block if the MSE is better than the previous best
                if (mse < minMSE || minMSE == -1)
                {
                    minMSE = mse;
                    dx = i - x_0;
                    dy = j - y_0;
                }
            }
        }

        return vector<double>{dx, dy};
    }
};

#endif
