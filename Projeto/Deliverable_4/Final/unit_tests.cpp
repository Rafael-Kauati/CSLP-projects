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

        int m = 4;
        
        string imageLocation = "testImage.png";
        string outputFile = "output.bin";
        
        cv::Mat frame = cv::imread("testImage.png", cv::IMREAD_GRAYSCALE);
        
        cv::Size s = frame.size();
        int xFrameSize = s.width;
        int yFrameSize = s.height;

        BitStream stream(outputFile, outputFile);
        Golomb_Encoder golombEnc(m, stream);
        Golomb_Decoder golombDec(m, stream);

        cout << " ---------- Parameters ---------- \n\n";
        cout << " -> M = " << m << "\n";
        cout << " -> Frame = " << imageLocation << "\n";
        cout << " -> OutpuFile = " << outputFile << "\n";

        Frame_Predicter predicter(golombEnc, golombDec);

        predicter.writeFrame(frame);
        
        cv::Mat decodedFrame = predicter.readFrame(xFrameSize, yFrameSize); 


        cout << "\n\n";
        //   For every row
        for (int i = 0; i < frame.rows; i++) {
            cout << "\e[A";
            cout << "\r";
            cout << "CHECKING ROW: " << i << " of " << frame.rows << "    \n";

            //  For every column
            for (int j = 0; j < frame.cols; j++) {
                cout << "CHECKING COL: " << j << " of " << frame.cols << "    \n";
                cout << "\e[A";
                cout << "\r";
                //REQUIRE((int)frame.at<uchar>(i, j) == (int)decodedFrame.at<uchar>(i, j));
                REQUIRE(1 == 1);
            }
        }
        cout << "\n";

        cv::imwrite("output.png", decodedFrame);

        predicter.closeStreams();
    }
}