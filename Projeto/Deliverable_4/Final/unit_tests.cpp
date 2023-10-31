// Created by PRamos on 31-10-2023.
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include "Frame_Predicter.h"
#include "Golomb.cpp"

using namespace std;

TEST_CASE("Frame Prediction, Golomb encoding and BitStream Writing") {

    SECTION("Frame To File") {

        int m = 4;
        
        string imageLocation = "testImage.png";
        string outputFile = "output.bin";
        
        cv::Mat frame = cv::imread("testImage.png", cv::IMREAD_GRAYSCALE);
        BitStream stream("", outputFile);
        Golomb_Encoder golomb(m, stream);

        cout << " ---------- Parameters ---------- \n\n";
        cout << " -> M = ", m;
        cout << " -> Frame = ", imageLocation;
        cout << " -> OutpuFile = ", outputFile;

        Frame_Predicter predicter(golomb);

        predicter.writeFrame(frame);

        REQUIRE(1 == 1);

        golomb.close();
    }
}