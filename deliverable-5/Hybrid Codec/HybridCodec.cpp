#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <cmath>
#include "Golomb.hpp"

using namespace std;
using namespace cv;
class HybridCodec
{
private:
    string filename, outputfile;
    int BLOCK_SIZE;
    int SEARCH_SIZE;
    Golomb g;
    
public:
    HybridCodec(/* args */);
    ~HybridCodec();
    encode()
};

HybridCodec::HybridCodec(string filename, string outputfile ,int blockSize = 8, int searchSize=16)
{
    this->filename = filename;
    this->outputfile = outputfile;
    this->BLOCK_SIZE = blockSize;
    this->SEARCH_SIZE = searchSize;
}


HybridCodec::~HybridCodec()
{
}

void decode() {
    int count = 1;

    Mat prevFrame;
    Mat frame;
    VideoCapture cap(filename);


    // read the first encoded block
    Mat decodedBlock;
    g.decodeBlock(decodedBlock);
    Mat decodedChannel(decodedBlock.size(), decodedBlock.type());

    // create a BlockSearch instance
    BlockSearch blockSearch(BLOCK_SIZE, SEARCH_SIZE);

    while (!decodedBlock.empty()) {
        int dx = g.decode();
        int dy = g.decode();

        Mat currentBlock;
        blockSearch.applyMotionCompensation(prevFrame, currentBlock, dx, dy);

        Mat reconstructedBlock;
        add(currentBlock, decodedBlock, reconstructedBlock);

        decodedChannel(Rect(0, 0, BLOCK_SIZE, BLOCK_SIZE)) = reconstructedBlock;

        g.decodeBlock(decodedBlock);

        if (decodedBlock.empty()) {
            Mat decodedFrame;
            merge(channels, decodedFrame);

            outputVideo.write(decodedFrame);

            prevFrame = decodedFrame;
            count++;

            g.decodeBlock(decodedBlock);
            decodedChannel = Mat(decodedBlock.size(), decodedBlock.type());
        }
    }


}


void encode() {
    int count = 1;

    Mat prevFrame;
    Mat frame;

    // get the first frame
    VideoCapture cap(filename);
    cap >> prevFrame;

    // loop through the video
    while(!prevFrame.empty()) {
        cap >> frame;
        // if the frame is empty, break immediately
        if(frame.empty()) {
            break;
        }
        // split the frame into channels
        split(prevFrame, channels);
        split(frame, channels);

        BlockSearch blockSearch(BLOCK_SIZE, SEARCH_SIZE);
        
        // loop through the channels
        for(int i = 0; i < channels.size(); i++) {
            // get the current channel
            Mat channel = channels[i];
            // get the height and width of the channel
            int height = channel.rows;
            int width = channel.cols;

            // loop through the channel in blocks

            for(int y = 0; y < height; y += BLOCK_SIZE) {
                for(int x = 0; x < width; x += BLOCK_SIZE) {
                    Mat block = channel(Rect(x, y, BLOCK_SIZE, BLOCK_SIZE));
                    // get the best block
                    vector<int> bestBlock = blockSearch.findBestBlock(prevFrame, block, x, y);
                    // get the best block's coordinates
                    int x_0 = bestBlock[0];
                    int y_0 = bestBlock[1];
                    // get the best block
                    Mat bestBlock = prevFrame(Rect(x_0, y_0, BLOCK_SIZE, BLOCK_SIZE));

                    // get the diff between the best block and the current block
                    Mat diff;
                    subtract(block, bestBlock, diff);
                                        
                    // encode the diff and the deslocation vector
                    g.encodeBlock(diff);
                    g.encode(x - x_0);
                    g.encode(y - y_0);

                }
            }
        }

        // update the previous frame
        prevFrame = frame;
        count++;
    }
}


