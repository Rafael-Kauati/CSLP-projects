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

TEST_CASE("Frame Encoding/Decoding") {

    SECTION("Single Frame, GreyScale") {

        cout << " ------------- ---------- ------------- \n";
        cout << " --- SINGLE FRAME ENCODING/DECODING --- \n";
        cout << " ---           Grey scale           --- \n";
        cout << " ------------- ---------- ------------- \n";
        int m = 16;
        
        string imageLocation = "TestFiles/testImage.png";
        string outputBinFile = "BinOutput/output.bin";
        string outputImgFile = "OutputFiles/output.png";
        
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
        predicterEnc.writeFrame(frame, 6);

        predicterEnc.closeStreams();
        

        Frame_Predicter predicterDec(outputBinFile, "");
        
        cout << "\n ---------- Read Parameters ---------- \n";
        predicterDec.readParams();
        cout << " -> OK\n";

        cout << "\n ------------ Read Frame ------------ \n";
        //  Repeat this for every frame
        cv::Mat decodedFrame = predicterDec.readFrame(6);

        predicterDec.closeStreams();

        cout << "\n ------------ Check Frame ------------ \n";
        cout << "\n";
        //   For every row
        for (int i = 0; i < yFrameSize; i++) {
            cout << "\e[A";
            cout << "\r";
            cout << " -> CHECKING ROW: " << i+1 << " of " << yFrameSize << "    \n";

            //  For every column
            for (int j = 0; j < xFrameSize; j++) {
                /* cout << " -> CHECKING COL: " << j+1 << " of " << xFrameSize << "                   \n";
                cout << "\e[A";
                cout << "\r"; */
                REQUIRE((int)frame.at<uchar>(i, j) == (int)decodedFrame.at<uchar>(i, j));
            }
        }
        cout << "\n\n\n";

        cv::imwrite(outputImgFile, decodedFrame);

    }

    SECTION("Single Frame, RGB") {

        cout << " ------------- ---------- ------------- \n";
        cout << " --- SINGLE FRAME ENCODING/DECODING --- \n";
        cout << " ---               RGB              --- \n";
        cout << " ------------- ---------- ------------- \n";
        int m = 16;
        
        string imageLocation = "TestFiles/testImageRGB.jpg";
        string outputBinFile = "BinOutput/output.bin";
        string outputImgFile = "OutputFiles/outputRGB.png";
        
        cv::Mat frame = cv::imread(imageLocation);
        
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
        predicterEnc.writeFrameRGB(frame, 6);

        predicterEnc.closeStreams();
        

        Frame_Predicter predicterDec(outputBinFile, "");
        
        cout << "\n ---------- Read Parameters ---------- \n";
        predicterDec.readParams();
        cout << " -> OK\n";

        cout << "\n ------------ Read Frame ------------ \n";
        //  Repeat this for every frame
        cv::Mat decodedFrame = predicterDec.readFrameRGB(6);

        predicterDec.closeStreams();

        cout << "\n ------------ Check Frame ------------ \n";
        cout << "\n";
        //   For every row
        for (int i = 0; i < yFrameSize; i++) {
            cout << "\e[A";
            cout << "\r";
            cout << " -> CHECKING ROW: " << i+1 << " of " << yFrameSize << "    \n";

            //  For every column
            for (int j = 0; j < xFrameSize; j++) {
                /* cout << " -> CHECKING COL: " << j+1 << " of " << xFrameSize << "                   \n";
                cout << "\e[A";
                cout << "\r"; */
                REQUIRE(frame.at<cv::Vec3b>(i, j) == decodedFrame.at<cv::Vec3b>(i, j));
            }
        }
        cout << "\n\n\n";

        cv::imwrite(outputImgFile, decodedFrame);

    }
}

TEST_CASE("Video Encoding/Decoding") {
    SECTION("Complete Video (array of frames)") {

        cout << " ------------- ---------- ------------- \n";
        cout << " -- COMPLETE VIDEO ENCODING/DECODING -- \n";
        cout << " ------------- ---------- ------------- \n";
        int m = 16;
        
        string videoLocation = "TestFiles/testVideoSmaller.mkv";
        string outputBinFile = "BinOutput/output.bin";
        string outputVidFile = "OutputFiles/output.mkv";
        
        cv::VideoCapture video(videoLocation);
        
        if (!video.isOpened()) {
            cout << " ERROR: Cannot read video file!\n";
            return;
        }

        int xFrameSize = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
        int yFrameSize = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
        int numFrames = (int)video.get(cv::CAP_PROP_FRAME_COUNT);
        int fps = (int)video.get(cv::CAP_PROP_FPS);

        cout << " ------------- Parameters ------------- \n";
        cout << " -> M = " << m << "\n";
        cout << " -> Video = " << videoLocation << "\n";
        cout << " -> Video Size = " << xFrameSize << "x" << yFrameSize << "\n";
        cout << " -> Output Bin File = " << outputBinFile << "\n";
        cout << " -> Output Vid File = " << outputVidFile << "\n";

        Frame_Predicter predicterEnc("", outputBinFile);

        cout << "\n ---------- Write Parameters ---------- \n";
        predicterEnc.writeParams(m, xFrameSize, yFrameSize, 1, numFrames, fps);
        cout << " -> OK\n";

        cout << "\n ------------ Write Video ------------ \n";

        //  Repeat this for every frame
        predicterEnc.writeVideo(video, 6);

        predicterEnc.closeStreams();
        

        Frame_Predicter predicterDec(outputBinFile, "");
        
        cout << "\n ---------- Read Parameters ---------- \n";
        predicterDec.readParams();
        cout << " -> OK\n";

        cout << "\n ------------ Read Video ------------ \n";
        //  Repeat this for every frame
        predicterDec.readVideo(outputVidFile, 6);

        predicterDec.closeStreams();

        cout << "\n ------------ Check Video ------------ \n";
        cout << "\n";

        //  Reopen the original video
        video = cv::VideoCapture(videoLocation);
        //  Open the decoded video
        cv::VideoCapture decodedVideo(outputVidFile);

        cv::Mat decodedFrame;
        cv::Mat originalFrame;
        bool readOriginal, readDecoded;
        //  For every frame CHANGE TO ONE LATER
        for (int frameIndex = 0; frameIndex < 1; frameIndex++) {
            readOriginal = video.read(originalFrame);
            readDecoded = decodedVideo.read(decodedFrame);
            cout << "\e[A";
            cout << "\r";
            cout << " -> CHECKING Frame: " << frameIndex+1 << " of " << numFrames << "    \n";

            //  Last frame has been read
            if (!readOriginal) {
                cout << "ERROR! Tried reading non existent frame from the original video!\n";
                return;
            }
            if (!readDecoded) {
                cout << "ERROR! Tried reading non existent frame from the decoded video!\n";
                return;
            }

            cout << "\n";

            //  For every row
            for (int i = 0; i < yFrameSize; i++) {
                cout << "\e[A";
                cout << "\r";
                cout << " -> CHECKING ROW: " << i+1 << " of " << yFrameSize << "    \n";

                //  For every column
                for (int j = 0; j < xFrameSize; j++) {
                    REQUIRE(originalFrame.at<cv::Vec3b>(i, j) == decodedFrame.at<cv::Vec3b>(i, j));
                }
            }
            cout << "\n";
        }
    }
}