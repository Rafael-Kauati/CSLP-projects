#ifndef HybridCodec_CPP
#define HybridCodec_CPP

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <cmath>
#include "../Golomb/Golomb.cpp"
#include "Frame_Predicter.h"
#include "BlockSearch.cpp"

using namespace std;
using namespace cv;
class HybridCodec
{
private:
    string inputfile, outputfile;
    int BLOCK_SIZE;
    int SEARCH_SIZE;
    int frequency;
    int mParam;
    int fileType;
    int xFrameSize;
    int yFrameSize;
    int fps;
    int numFrames;
    int block_size;
    int search_area;
    int intraframe_period;

public:
    Frame_Predicter p;

    HybridCodec(string inputfile, string outputfile, int blockSize = 8, int searchSize = 8, int frequency = 100)
        : p(inputfile, outputfile)
    {
        this->inputfile = inputfile;
        this->outputfile = outputfile;
        this->BLOCK_SIZE = blockSize;
        this->SEARCH_SIZE = searchSize;
        this->frequency = frequency;
    }

    ~HybridCodec()
    {
    }

    void writeParams(int newmParam, int newxFrameSize, int newyFrameSize,
                    int newfileType, int newnumFrames = 1, int newfps = 1,
                    int newblock_size=1, int newsearch_area=1, int newintraframe_period=1)
    {
        this->mParam = newmParam;
        this->fileType = newfileType;
        this->xFrameSize = newxFrameSize;
        this->yFrameSize = newyFrameSize;
        this->fps = newfps;
        this->numFrames = newnumFrames;
        this->block_size = newblock_size;
        this->search_area = newsearch_area;
        this->intraframe_period = newintraframe_period;
        p.writeParams(newmParam, newxFrameSize, newyFrameSize, newfileType, newnumFrames, newfps, newblock_size, newsearch_area, newintraframe_period);
    }

    void readParams()
    {
        vector<int> params = p.readParams();
    
        //  Read the m parameter with 1 byte (max: 255)
        this->mParam = params[0];
        //  Read the x and y frame sizes with 2 bytes each (max: 65,535)
        this->xFrameSize = params[1];
        this->yFrameSize = params[2];
        //  Read the file format index with 1 byte (max: 255)
        this->fileType = params[3];
        //  Read the number of frames with 4 bytes (max: 2,147,483,647)
        this->numFrames = params[4];
        //  Read the FPS of the video with 1 byte (max: 255)
        this->fps = params[5];
        //  Read the block size of the video with 2 bytes (max: 65,535)
        this->block_size = params[6];
        //  Read the search area size of the video with 2 bytes (max: 65,535)
        this->search_area = params[7];
        //  Read the period between intraframes of the video with 1 byte (max: 255)
        this->intraframe_period = params[8];
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

    vector<cv::Mat> decodeVideo(string outputVidFile)
    {
        int fileT;
        if (this->fileType == 1)
        {
            fileT = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
        }
        Mat decodedFrame;
        Mat prevFrame;

        vector<cv::Mat> frameVector;
        
        cv::VideoWriter decodedVideoWriter(outputVidFile, fileT, (double)this->fps, cv::Size(this->xFrameSize, this->yFrameSize), 1);

        // get the best block
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        for (int frameIndex = 0; frameIndex < this->numFrames; frameIndex++)
        {
            begin = std::chrono::steady_clock::now();
            if (frameIndex % frequency == 0)
            {
                decodedFrame = p.readFrameColour();
            }
            else
            {
                decodedFrame = decodeFrame(prevFrame);
            }

            prevFrame = decodedFrame;

            if (decodedFrame.empty())
            {
                break;
            }

            frameVector.push_back(decodedFrame);
            decodedVideoWriter.write(decodedFrame);

            end = std::chrono::steady_clock::now();
            cout << " -> Time for frame "<< frameIndex << " : " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "\n";
        }
        decodedVideoWriter.release();

        return frameVector;

    }

    Mat decodeFrame(Mat prevFrame)
    {
        std::vector<cv::Mat> channels;
        cv::Mat ColourFrame;
        cv::Mat decodedFrame;

        vector<Mat> prevChannels;
        split(prevFrame, prevChannels);

        channels.push_back(decodeChannel(prevChannels[0]));
        channels.push_back(decodeChannel(prevChannels[1]));
        channels.push_back(decodeChannel(prevChannels[2]));

        cv::merge(channels, ColourFrame);

        return ColourFrame;
    }


    Mat decodeChannel(Mat prevFrame)
    {
        int x_diff = p.decode();
        int y_diff = p.decode();

        // get the height and width of the channe
        int height = this->yFrameSize;
        int width = this->xFrameSize;
        
        cv::Mat decodedFrame = cv::Mat::zeros(cv::Size(width, height), cv::IMREAD_GRAYSCALE);

        // loop through the channel in blocks
        // get the best block
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        for (int y = 0; y < height; y += this->BLOCK_SIZE)
        {
            for (int x = 0; x < width; x += this->BLOCK_SIZE)
            {

                // get the diff between the best block and the current block
                Mat diff = p.decodeBlock(this->BLOCK_SIZE);

                // get the best block's coordinates
                int xPos = p.decode();
                int yPos = p.decode();
                Mat lastBlock = prevFrame(Rect(x+xPos, y+yPos, this->BLOCK_SIZE, this->BLOCK_SIZE));


                for (int yd = y; yd < y + this->BLOCK_SIZE; yd++) {
                    for (int xd = x; xd < x + this->BLOCK_SIZE; xd++) {
                        decodedFrame.at<uchar>(yd, xd) = diff.at<uchar>(yd - y, xd - x) + lastBlock.at<uchar>(yd - y, xd - x);
                    }
                }
            }
        }

        return decodedFrame;
    }
    

    void encodeVideo(cv::VideoCapture cap) {
        int count = 0;
        Mat frame;
        Mat prevFrame;

        //read the frame
        cap >> frame;

        // check if the video can be opened
        if (!cap.isOpened())
        {
            cout << "Error opening video stream or file" << endl;
            return;
        }

        // get the best block
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        // loop through the video
        while (!frame.empty())
        {
            begin = std::chrono::steady_clock::now();

            if (count % frequency == 0)
            {
                // if is the frequency-th frame, encode the frame with intra-frame coding
                p.writeFrameColour(frame);
            }
            else
            {
                // if is not the frequency-th frame, encode the frame with inter-frame coding
                encodeFrame(frame, prevFrame);
            }

            prevFrame = frame;
            count++;

            //read the frame
            cap >> frame;

            end = std::chrono::steady_clock::now();
            cout << " -> Time for frame "<< count << " : " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "\n";
        }
    }

    void encodeFrame(Mat frame, Mat prevFrame)
    {
        // split the frame into channels
        vector<Mat> channels;
        split(frame, channels);

        // split the previous frame into channels
        vector<Mat> prevChannels;
        split(prevFrame, prevChannels);

        // encode each channel
        encodeChannel(channels[0], prevChannels[0]);
        encodeChannel(channels[1], prevChannels[1]);
        encodeChannel(channels[2], prevChannels[2]);
    }

    void encodeChannel(Mat channel, Mat prevChannel)
    {
        // get the height and width of the channe
        int height = this->yFrameSize;
        int width = this->xFrameSize;

        BlockSearch bSearch = BlockSearch(this->BLOCK_SIZE, this->SEARCH_SIZE, 4);

        // loop through the channel in blocks
        // get the best block
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        for (int y = 0; y < height; y += this->BLOCK_SIZE)
        {
            for (int x = 0; x < width; x += this->BLOCK_SIZE)
            {
                Mat block = channel(Rect(x, y, this->BLOCK_SIZE, this->BLOCK_SIZE));

                vector<double> bestBlock = bSearch.findBestBlock(prevChannel, block, x, y);

                // get the best block's coordinates
                int x_0 = (int)bestBlock[0];
                int y_0 = (int)bestBlock[1];

                // get the diff between the best block and the current block
                Mat diff;
                Mat bestBlockMat = channel(Rect(x+x_0, y+y_0, this->BLOCK_SIZE, this->BLOCK_SIZE));

                subtract(block, bestBlockMat, diff);

                // encode the diff and the deslocation vector
                p.encodeBlock(diff);
            
                // write deslocation vector to file
                p.encode(x_0);
                p.encode(y_0);
            }
        }
    }

};

#endif