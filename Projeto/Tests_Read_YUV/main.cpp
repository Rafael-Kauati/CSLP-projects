#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;

//  YUV DOCS: https://wiki.multimedia.cx/index.php/YUV4MPEG2

int main() {
    std::cout << " ---------- YUV 4:4:4 Reader Test ---------- \n";

    //  First line
    string dataLine;
    //  Y4M file (YUV video)
    ifstream yuvFile("outputDucks00.y4m", fstream::in);

    //  Get the first line
    getline( yuvFile, dataLine );
    istringstream iss(dataLine);
    string str;

    //  Video atributes
    int frameWidth = 0;
    int frameHeight = 0;
    int videoFPS = 0;
    
    //  Parse the first line of the file (video atributes)
    while (getline( iss, str, ' ' )) {
        if (str[0] == 'W') {
            frameWidth = stoi(str.erase(0,1));
        }
        else if (str[0] == 'H') {
            frameHeight = stoi(str.erase(0,1));
        }
        else if (str[0] == 'F') {
            videoFPS = stoi(str.erase(0,1));
        }
        else if (str[0] == 'C') {
            if (stoi(str.erase(0,1)) != 444) {
                cout << "ERROR! Please provide a YUV file in the 4:4:4 format! Other formats may give unexpected results!";
                return 1;
            }
        }
    }

    cout << " -> IMAGE SIZE: y = " << frameHeight << " | x = " << frameWidth << "    \n\n";
    getline(yuvFile, str);

    char ch;
    string lastFiveChars;
    int frameCount = 0;
    vector<vector<int>> yframe;
    vector<vector<int>> uframe;
    vector<vector<int>> vframe;
    
    //  Parse 3 (y, u and v) times width * height 
    //while (frameCount < 1) {

    int numPixelsPerFrame = frameWidth * frameHeight;
    //  Read all frame rows
    for(int pixelHeightIdx = 0; pixelHeightIdx < frameHeight; pixelHeightIdx++) {
        vector<int> rowVector;
        
        //  Read all frame columns
        for(int pixelWidthIdx = 0; pixelWidthIdx < frameWidth; pixelWidthIdx++) {
            cout << "\e[A";
            cout << "\r";
            cout << " -> READING PIXEL: y = " << pixelHeightIdx << " | x = " << pixelWidthIdx << "    \n";
            yuvFile.get(ch);
            rowVector.push_back(int(ch));
        }

        yframe.push_back(rowVector);
    }

    cout << "HERE" << endl;

    frameCount++;

    //}


    cv::Mat finalFrame = cv::Mat(frameHeight, frameWidth, cv::IMREAD_GRAYSCALE);

    //  Write img to file ONLY FOR VISUAL TESTING
    for(int pixelHeightIdx = 0; pixelHeightIdx < frameHeight; pixelHeightIdx++) {
        //  Read all frame columns
        for(int pixelWidthIdx = 0; pixelWidthIdx < frameWidth; pixelWidthIdx++) {
            cout << "\e[A";
            cout << "\r";
            cout << " -> CHECKING PIXEL: y = " << pixelHeightIdx << " | x = " << pixelWidthIdx << "    \n";
            finalFrame.at<uchar>(pixelHeightIdx, pixelWidthIdx) = yframe.at(pixelHeightIdx).at(pixelWidthIdx);
        }
    }
    //  Write the final image to the output file
    cv::imwrite("testImgFile.png", finalFrame);


    cout << "\n";
    
    return 0;
}
