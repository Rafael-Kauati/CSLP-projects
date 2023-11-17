// Created by PRamos on 31-10-2023.
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include "Frame_Predicter.h"
#include "Golomb.cpp"
#include "BitStream.h"

using namespace std;

TEST_CASE("Frame Prediction, Golomb encoding and BitStream Writing") {

    SECTION("Frame To File") {

        int m = 8;
        
        string imageLocation = "testImage.png";
        string outputBinFile = "output.bin";
        string outputImgFile = "output.png";
        
        cv::Mat frame = cv::imread(imageLocation, cv::IMREAD_GRAYSCALE);
        
        int xFrameSize = frame.cols;
        int yFrameSize = frame.rows;

        cout << " ------------- Parameters ------------- \n";
        cout << " -> M = " << m << "\n";
        cout << " -> Frame = " << imageLocation << "\n";
        cout << " -> Frame Size = " << xFrameSize << "x" << yFrameSize << "\n";
        cout << " -> Output Bin File = " << outputBinFile << "\n";
        cout << " -> Output Img File = " << outputImgFile << "\n";

        Frame_Predicter predicterEnc("", outputBinFile);

        cout << "\n ---------- Write Parameters ---------- \n";
        predicterEnc.writeParams(m, xFrameSize, yFrameSize, 1);
        cout << " -> OK\n";

        cout << "\n ------------ Write Frame ------------ \n";
        //  Repeat this for every frame
        predicterEnc.writeFrame(frame, 1);

        predicterEnc.closeStreams();
        

        Frame_Predicter predicterDec(outputBinFile, "");
        
        cout << "\n ---------- Read Parameters ---------- \n";
        predicterDec.readParams();
        cout << " -> OK\n";

        cout << "\n ------------ Read Frame ------------ \n";
        //  Repeat this for every frame
        cv::Mat decodedFrame = predicterDec.readFrame(1);

        predicterDec.closeStreams();

        int lastF = 0;

        cout << "\n ------------ Check Frame ------------ \n";
        cout << "\n";
        //   For every row
        for (int i = 0; i < yFrameSize; i++) {
            cout << "\e[A";
            cout << "\r";
            cout << " -> CHECKING ROW: " << i+1 << " of " << yFrameSize << "    \n";

            //  For every column
            for (int j = 0; j < xFrameSize; j++) {
                cout << " -> CHECKING COL: " << j+1 << " of " << xFrameSize << "                   \n";
                cout << "\e[A";
                cout << "\r";
                REQUIRE((int)frame.at<uchar>(i, j) == (int)decodedFrame.at<uchar>(i, j));
                lastF = (int)frame.at<uchar>(i, j);
            }
        }
        cout << "\n";

        cv::imwrite(outputImgFile, decodedFrame);

    }
}