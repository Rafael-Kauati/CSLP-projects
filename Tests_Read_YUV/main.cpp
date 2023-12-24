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

    cout << " -> VIDEO FPS: " << videoFPS << "    \n";
    cout << " -> IMAGE SIZE: y = " << frameHeight << " | x = " << frameWidth << "    \n\n";
    getline(yuvFile, str);

    char ch;
    string lastFiveChars;
    int frameCount = 0;
    int colourCount = 0;
    vector<vector<int>> readframe[3];
    
    //  Parse 3 (y, u and v) times width * height 
    while (colourCount < 3) {
        cout << "\e[A";
        cout << "\r";
        cout << " -> READING COLOUR: " << colourCount << "    \n";
        //  Read all frame rows
        for(int pixelHeightIdx = 0; pixelHeightIdx < frameHeight; pixelHeightIdx++) {
            vector<int> rowVector;
            
            //  Read all frame columns
            for(int pixelWidthIdx = 0; pixelWidthIdx < frameWidth; pixelWidthIdx++) {
                yuvFile.get(ch);
                rowVector.push_back(int(ch));
            }

            readframe[colourCount].push_back(rowVector);
        }

        /* cout << "HERE" << endl; */

        colourCount++;

    }


    cv::Vec3b pixelValue;
    cv::Mat finalFrame(frameHeight, frameWidth, CV_8UC3);

    cout << " -> CREATING FINAL IMAGE:\n";

    //  Write img to file ONLY FOR VISUAL TESTING
    for(int pixelHeightIdx = 0; pixelHeightIdx < frameHeight; pixelHeightIdx++) {
        //  Read all frame columns
        for(int pixelWidthIdx = 0; pixelWidthIdx < frameWidth; pixelWidthIdx++) {

            pixelValue = cv::Vec3b(readframe[0].at(pixelHeightIdx).at(pixelWidthIdx), readframe[1].at(pixelHeightIdx).at(pixelWidthIdx), readframe[2].at(pixelHeightIdx).at(pixelWidthIdx));
            finalFrame.at<cv::Vec3b>(pixelHeightIdx, pixelWidthIdx) = pixelValue;
        }
    }
    //  Write the final image to the output file
    cv::imwrite("testImgFile.png", finalFrame);

    cout << "       => DONE!\n";

    return 0;
}
