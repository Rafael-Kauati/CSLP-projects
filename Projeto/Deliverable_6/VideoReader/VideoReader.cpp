#ifndef VideoReader_CPP
#define VideoReader_CPP

#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <opencv2/opencv.hpp>

using namespace std;


class VideoReader
{
private:
    int VIDEO_FPS;
    int FRAME_HEIGHT;
    int FRAME_WIDTH;
    bool READ_ERROR;
    bool VIDEO_END;
    ifstream yuvFile;

public:
    //  Instanciate the video reader by reading all the 
    // atributes stored in the y4m file's first line
    VideoReader(string fileName) {
        this->READ_ERROR = false;
        this->VIDEO_END = false;

        //  First line
        string dataLine;
        //  Y4M file (YUV video)
        this->yuvFile = ifstream(fileName, fstream::in);

        //  Get the first line
        getline(this->yuvFile, dataLine);
        //  Read the first line
        istringstream iss(dataLine);
        string str;
        
        //  Parse the first line of the file (video atributes)
        while (getline(iss, str, ' ')) {
            if (str[0] == 'W') {
                this->FRAME_WIDTH = stoi(str.erase(0,1));
            }
            else if (str[0] == 'H') {
                this->FRAME_HEIGHT = stoi(str.erase(0,1));
            }
            else if (str[0] == 'F') {
                this->VIDEO_FPS = stoi(str.erase(0,1));
            }
            else if (str[0] == 'C') {
                if (stoi(str.erase(0,1)) != 444) {
                    cout << "ERROR! Please provide a YUV file in the 4:4:4 format! Other formats may give unexpected results!";
                    this->READ_ERROR = true;
                }
            }
        }
    };

    /**
     * @brief Destructor for the VideoReader class.
     */
    ~VideoReader(){};

    int videoEnd() {
        return this->VIDEO_END;
    }
    int getVideoFPS() {
        return this->VIDEO_FPS;
    }
    int getFrameHeigth() {
        return this->FRAME_HEIGHT;
    }
    int getFrameWidth() {
        return this->FRAME_WIDTH;
    }
    bool readError() {
        return this->READ_ERROR;
    }

    //  Returns an cv::Mat with the respective Y, U and V matrix of pixels
    cv::Mat readNextYUVFrame() {
        string str;
        cv::Mat readframe = cv::Mat::zeros(cv::Size(this->FRAME_WIDTH, this->FRAME_HEIGHT), CV_8UC3);
        std::vector<cv::Mat> channels;
        char ch;
        int colourCount = 0;

        if (this->yuvFile.peek() == EOF) {
            this->VIDEO_END = true;
            return readframe;
        }

        //  Skip the "FRAME\n" line
        for (int charIdx = 0; charIdx < 6; charIdx ++) {
            yuvFile.get(ch);
        }
    
        //  Parse 3 (y, u and v) * width * height 
        while (colourCount < 3) {
            cv::Mat tempframe = cv::Mat::zeros(cv::Size(this->FRAME_WIDTH, this->FRAME_HEIGHT), cv::IMREAD_GRAYSCALE);

            //  Read all frame rows
            for(int pixelHeightIdx = 0; pixelHeightIdx < this->FRAME_HEIGHT; pixelHeightIdx++) {
                vector<int> rowVector;
                
                //  Read all frame columns
                for(int pixelWidthIdx = 0; pixelWidthIdx < this->FRAME_WIDTH; pixelWidthIdx++) {

                    if (this->yuvFile.peek() == EOF) {
                        this->VIDEO_END = true;
                        return readframe;
                    }

                    yuvFile.get(ch);
                    tempframe.at<uchar>(pixelHeightIdx, pixelWidthIdx) = int(ch);
                }
            }

            channels.push_back(tempframe);
            colourCount++;
        }

        //  Merge the current frame from the decoded channels
        cv::merge(channels, readframe);

        return readframe;
    }
    
    //  IMPORTANT: this simple compare function was obtained from here, we did not write it:
    //  https://stackoverflow.com/questions/6163611/compare-two-files
    static bool compareFiles(const std::string& p1, const std::string& p2) {
        std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
        std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

        if (f1.fail() || f2.fail()) {
            return false; //file problem
        }

        if (f1.tellg() != f2.tellg()) {
            return false; //size mismatch
        }

        //seek back to beginning and use std::equal to compare contents
        f1.seekg(0, std::ifstream::beg);
        f2.seekg(0, std::ifstream::beg);
        return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                            std::istreambuf_iterator<char>(),
                            std::istreambuf_iterator<char>(f2.rdbuf()));
    }
};

#endif
