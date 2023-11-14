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
        string outputFile = "output.bin";
        
        cv::Mat frame = cv::imread(imageLocation, cv::IMREAD_GRAYSCALE);
        
        int xFrameSize = frame.cols;
        int yFrameSize = frame.rows;

        BitStream outStream("", outputFile);
        BitStream inStream(outputFile, "");
        Golomb_Encoder golombEnc(m, outStream);
        Golomb_Decoder golombDec(m, inStream);

        cout << " ---------- Parameters ---------- \n\n";
        cout << " -> M = " << m << "\n";
        cout << " -> Frame = " << imageLocation << "\n";
        cout << " -> OutpuFile = " << outputFile << "\n";

        Frame_Predicter predicterEnc(golombEnc, golombDec);

        predicterEnc.writeFrame(frame, 1);
        predicterEnc.closeStreams();
        
        Frame_Predicter predicterDec(golombEnc, golombDec);
        cv::Mat decodedFrame = predicterDec.readFrame(xFrameSize, yFrameSize, 1); 
        predicterDec.closeStreams();

        int lastF = 0;

        cout << "\n\n";
        //   For every row
        for (int i = 0; i < frame.rows; i++) {
            cout << "\e[A";
            cout << "\r";
            cout << "CHECKING ROW: " << i << " of " << frame.rows << "    \n";

            //  For every column
            for (int j = 0; j < frame.cols; j++) {
                cout << "CHECKING COL: " << j << " of " << frame.cols << "   lastF> " << lastF << "                   \n";
                cout << "\e[A";
                cout << "\r";
                REQUIRE((int)frame.at<uchar>(i, j) == (int)decodedFrame.at<uchar>(i, j));
                lastF = (int)frame.at<uchar>(i, j);
                //REQUIRE(1 == 1);
            }
        }
        cout << "\n";

        cv::imwrite("output.png", decodedFrame);

    }
}