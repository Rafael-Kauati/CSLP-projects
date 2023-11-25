#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <cmath>
#include "../Golomb/Golomb.hpp"
#include "Frame_Predicter.h"

using namespace std;
using namespace cv;
class HybridCodec
{
private:
    string inputfile, outputfile;
    int BLOCK_SIZE;
    int SEARCH_SIZE;
    Golomb g;
    int frequency;

public:
    HybridCodec(/* args */);
    ~HybridCodec();
    encode();
    decode();
    close();
    Frame_Predicter p;

};

HybridCodec::HybridCodec(string inputfile, string outputfile, int blockSize = 8, int searchSize = 16, int frequency = 100)
: p(inputfile, outputfile)
{
    this->inputfile = inputfile;
    this->outputfile = outputfile;
    this->BLOCK_SIZE = blockSize;
    this->SEARCH_SIZE = searchSize;
    this->frequency = frequency;

}

HybridCodec::~HybridCodec()
{
}

void writeParams(int newmParam, int newxFrameSize, int newyFrameSize,
                 int newfileType, int newnumFrames=1, int newfps=1)

{
    p.writeParams(int newmParam, int newxFrameSize, int newyFrameSize, int newfileType, int newnumFrames=1, int newfps=1);
}


void readParams()
{
    p.readParams();
}

vector<cv::Mat> readVideo(string outputFile)
{
    return p.readVideo(outputFile);
}

void writeVideo(cv::VideoCapture video)
{
    p.writeVideo(video);
}

void close()
    {
        p.closeStreams();
    }

vector<cv::Mat> decode()
{
    int count = 0;

    Mat decodedFrame;

    vector<cv::Mat> frameVector;

    while (true)
    {
        if (count % frequency == 0)
        {
            Frame_Predicter fp;

            Mat intraCodedFrame = fp.readFrameColour(inputfile);

            decodedFrame = intraCodedFrame;
        }
        else
        {
            cout<< "\nDeconding inter-frames  at frame : "<< count<< "\n"<<endl;
            Mat diff = g.decodeBlock();
            int x_diff = g.decode();
            int y_diff = g.decode();

            Mat bestBlock = prevFrame(Rect(x_diff, y_diff, BLOCK_SIZE, BLOCK_SIZE));

            decodedFrame = bestBlock + diff;
        }


        frameVector.push_back(decodedFrame);

        count++;

        if (decodedFrame.empty())
        {
            break;
        }
    }
    return frameVector;

}


void encode()
{
    int count = 0;

    Mat prevFrame;
    Mat frame;

    // get the first frame
    VideoCapture cap(inputfile);
    cap >> prevFrame;

    // loop through the video
    while (!prevFrame.empty())
    {
        if (count % frequency == 0)
        {
            // if is the frequency-th frame, encode the frame with intra-frame coding
            Frame_Predicter fp;
            
            fp.writeFrameColour(prevFrame, outputfile);

            // encode the frame
            g.encodeBlock(prevFrame);
        }
        else
        {

            cap >> frame;
            // if the frame is empty, break immediately
            if (frame.empty())
            {
                break;
            }
            // split the frame into channels
            split(prevFrame, channels);
            split(frame, channels);

            BlockSearch blockSearch(BLOCK_SIZE, SEARCH_SIZE);

            // loop through the channels
            for (int i = 0; i < channels.size(); i++)
            {
                // get the current channel
                Mat channel = channels[i];
                // get the height and width of the channel
                int height = channel.rows;
                int width = channel.cols;

                // loop through the channel in blocks

                for (int y = 0; y < height; y += BLOCK_SIZE)
                {
                    for (int x = 0; x < width; x += BLOCK_SIZE)
                    {
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
        }

        // update the previous frame
        prevFrame = frame;
        count++;
    }
}
