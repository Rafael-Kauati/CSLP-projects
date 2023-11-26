// Created by PRamos on 31-10-2023.

/**
 * @file unit_tests.cpp
 * @brief Unit tests for frame and video encoding/decoding functionality.
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include "Predictor/Frame_Predicter.h"
#include "Golomb/Golomb.cpp"
#include "Predictor/BitStream.h"
#include <chrono>

using namespace std;

/**
 * @brief Test case for single frame encoding and decoding images.
 */
TEST_CASE("Frame Encoding/Decoding")
{

    /**
     * @brief Test the encoding and decoding of a single greyscale frame.
     *
     * This section of the test case focuses on the encoding and decoding of
     * a single greyscale frame. It uses a predefined image, performs encoding,
     * then decodes the frame and checks if the decoded frame matches the original.
     */
    SECTION("Single Frame, GreyScale")
    {

        cout << " ------------- ---------- ------------- \n";
        cout << " --- SINGLE FRAME ENCODING/DECODING --- \n";
        cout << " ---           Grey scale           --- \n";
        cout << " ------------- ---------- ------------- \n";

        //  Define the test variables here
        int m = 8;

        //  File system locations
        string imageLocation = "TestFiles/testImage.png";
        string outputBinFile = "BinOutput/output.bin";
        string outputImgFile = "OutputFiles/output.png";

        //  Open the input image frame capture
        cv::Mat frame = cv::imread(imageLocation, cv::IMREAD_GRAYSCALE);

        int xFrameSize = frame.cols;
        int yFrameSize = frame.rows;

        //  Print all the final parameters
        cout << " ------------- Parameters ------------- \n";
        cout << " -> M = " << m << "\n";
        cout << " -> Frame = " << imageLocation << "\n";
        cout << " -> Frame Size = " << xFrameSize << "x" << yFrameSize << "\n";
        cout << " -> Output Bin File = " << outputBinFile << "\n";
        cout << " -> Output Img File = " << outputImgFile << "\n";



        //        ENCODING
        //  Instanciate the Frame Predicter for encoding
        Frame_Predicter predicterEnc("", outputBinFile);

        //  Write the parameters needed for all the classes
        cout << "\n ---------- Write Parameters ---------- \n";
        predicterEnc.writeParams(m, xFrameSize, yFrameSize, 1);
        cout << " -> OK\n";

        //  Write the frame itself to the file (and time the execution)
        cout << "\n ------------ Write Frame ------------ \n";
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        predicterEnc.writeFrame(frame);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        cout << " -> Encode Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";

        //  Close the used streams
        predicterEnc.closeStreams();

        //        DECODING
        //  Instanciate the Frame Predicter for decoding
        Frame_Predicter predicterDec(outputBinFile, "");

        //  Read the parameters needed for all the classes
        cout << "\n ---------- Read Parameters ---------- \n";
        predicterDec.readParams();
        cout << " -> OK\n";

        //  Read the frame itself from the file (and time the execution)
        cout << "\n ------------ Read Frame ------------ \n";
        begin = std::chrono::steady_clock::now();

        cv::Mat decodedFrame = predicterDec.readFrame();

        end = std::chrono::steady_clock::now();
        cout << " -> Decode Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";

        //  Close the used classes
        predicterDec.closeStreams();

        //        TESTING
        //  Test all the pixels of the decoded frame against the original frame
        cout << "\n ------------ Check Frame ------------ \n";
        cout << "\n";
        //   For every row
        for (int i = 0; i < yFrameSize; i++)
        {
            cout << "\e[A";
            cout << "\r";
            cout << " -> CHECKING ROW: " << i + 1 << " of " << yFrameSize << "    \n";

            //  For every column
            for (int j = 0; j < xFrameSize; j++)
            {
                REQUIRE((int)frame.at<uchar>(i, j) == (int)decodedFrame.at<uchar>(i, j));
            }
        }
        cout << "\n\n\n";

        //  Write the final image to the output file
        cv::imwrite(outputImgFile, decodedFrame);
    }

    /**
     * @brief Test the encoding and decoding of a single YUV frame.
     *
     * This section of the test case focuses on the encoding and decoding of
     * a single YUV frame. It uses a predefined RGB image, performs encoding,
     * then decodes the frame and checks if the decoded frame matches the original.
     */
    SECTION("Single Frame, YUV")
    {

        cout << " ------------- ---------- ------------- \n";
        cout << " --- SINGLE FRAME ENCODING/DECODING --- \n";
        cout << " ---               YUV              --- \n";
        cout << " ------------- ---------- ------------- \n";

        //  Define the test variables here
        int m = 8;

        //  File system locations
        string imageLocation = "TestFiles/testImageRGB.jpg";
        string outputBinFile = "BinOutput/output.bin";
        string outputImgFile = "OutputFiles/outputRGB.png";

        //  Open the input image frame capture
        cv::Mat frame = cv::imread(imageLocation);

        int xFrameSize = frame.cols;
        int yFrameSize = frame.rows;

        //  Print all the final parameters
        cout << " ------------- Parameters ------------- \n";
        cout << " -> M = " << m << "\n";
        cout << " -> Frame = " << imageLocation << "\n";
        cout << " -> Frame Size = " << xFrameSize << "x" << yFrameSize << "\n";
        cout << " -> Output Bin File = " << outputBinFile << "\n";
        cout << " -> Output Img File = " << outputImgFile << "\n";

        //        ENCODING
        //  Instanciate the Frame Predicter for encoding
        Frame_Predicter predicterEnc("", outputBinFile);

        //  Write the parameters needed for all the classes
        cout << "\n ---------- Write Parameters ---------- \n";
        predicterEnc.writeParams(m, xFrameSize, yFrameSize, 1);
        cout << " -> OK\n";

        //  Write the frame itself to the file (and time the execution)
        cout << "\n ------------ Write Frame ------------ \n";
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        predicterEnc.writeFrameColour(frame);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        cout << " -> Encode Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";

        //  Close the used streams
        predicterEnc.closeStreams();

        //        DECODING
        //  Instanciate the Frame Predicter for decoding
        Frame_Predicter predicterDec(outputBinFile, "");

        //  Read the parameters needed for all the classes
        cout << "\n ---------- Read Parameters ---------- \n";
        predicterDec.readParams();
        cout << " -> OK\n";

        //  Read the frame itself from the file (and time the execution)
        cout << "\n ------------ Read Frame ------------ \n";
        begin = std::chrono::steady_clock::now();

        //  Repeat this for every frame
        cv::Mat decodedFrame = predicterDec.readFrameColour();

        end = std::chrono::steady_clock::now();
        cout << " -> Decode Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";

        //  Close the used classes
        predicterDec.closeStreams();

        //        TESTING
        //  Test all the pixels of the decoded frame against the original frame
        cout << "\n ------------ Check Frame ------------ \n";
        cout << "\n";
        //   For every row
        for (int i = 0; i < yFrameSize; i++)
        {
            cout << "\e[A";
            cout << "\r";
            cout << " -> CHECKING ROW: " << i + 1 << " of " << yFrameSize << "    \n";

            //  For every column
            for (int j = 0; j < xFrameSize; j++)
            {
                REQUIRE(frame.at<cv::Vec3b>(i, j) == decodedFrame.at<cv::Vec3b>(i, j));
            }
        }
        cout << "\n\n\n";

        cv::imwrite(outputImgFile, decodedFrame);
    }
}

/**
 * @brief Test case for video encoding and decoding.
 */
TEST_CASE("Video Encoding/Decoding")
{

    /**
     * @brief Test the encoding and decoding of a complete video.
     *
     * This section of the test case focuses on the encoding and decoding of
     * a complete video, represented as an array of frames. It reads a video
     * file, performs encoding, then decodes the video and checks if each
     * decoded frame matches the corresponding original frame.
     */
    SECTION("Complete Video (array of frames)")
    {

        cout << " ------------- ---------- ------------- \n";
        cout << " -- COMPLETE VIDEO ENCODING/DECODING -- \n";
        cout << " ------------- ---------- ------------- \n";

        //  Define the test variables here
        int m = 8;

        //  File system locations
        string defaultVideoLocation = "TestFiles/ducks_30_frames.y4m";
        string videoLocation = "";
        string outputBinFile = "BinOutput/output.bin";
        string outputVidFile = "OutputFiles/output.mp4";

        //  Ask for the file to read
        cout << "\n Please select the input video file: ";
        cout << "\n (empty for " << defaultVideoLocation << ") \n";
        cout << "        -=> ";
        getline(std::cin, videoLocation);
        
        if (videoLocation == "") {
            videoLocation = defaultVideoLocation;
        }

        //  Open the input video capture
        cv::VideoCapture video(videoLocation);

        if (!video.isOpened()) {
            cout << " ERROR: Cannot read video file!\n";
            return;
        }

        //  Calculate the video's metadata
        int xFrameSize = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
        int yFrameSize = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
        int numFrames = (int)video.get(cv::CAP_PROP_FRAME_COUNT);
        int fps = (int)video.get(cv::CAP_PROP_FPS);

        //  Print all the final parameters
        cout << "\n ------------- Parameters ------------- \n";
        cout << " -> M = " << m << "\n";
        cout << " -> Video = " << videoLocation << "\n";
        cout << " -> Video Size = " << xFrameSize << "x" << yFrameSize << "\n";
        cout << " -> Output Bin File = " << outputBinFile << "\n";
        cout << " -> Output Vid File = " << outputVidFile << "\n";

        //        ENCODING
        //  Instanciate the Frame Predicter for encoding
        Frame_Predicter predicterEnc("", outputBinFile);

        //  Write the parameters needed for all the classes
        cout << "\n ---------- Write Parameters ---------- \n";
        predicterEnc.writeParams(m, xFrameSize, yFrameSize, 1, numFrames, fps);
        cout << " -> OK\n";

        //  Write the video itself to the file (and time the execution)
        cout << "\n ------------ Write Video ------------ \n";
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        predicterEnc.writeVideo(video);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        cout << " -> Encode Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";

        //  Close the used classe
        predicterEnc.closeStreams();

        //  Instanciate the Frame Predicter for decoding
        Frame_Predicter predicterDec(outputBinFile, "");

        //  Read the parameters needed for all the classes
        cout << "\n ---------- Read Parameters ---------- \n";
        predicterDec.readParams();
        cout << " -> OK\n";

        //  Read the video itself from the file (and time the execution)
        cout << "\n ------------ Read Video ------------ \n";
        begin = std::chrono::steady_clock::now();

        vector<cv::Mat> decodedVideo = predicterDec.readVideo(outputVidFile);

        end = std::chrono::steady_clock::now();
        cout << " -> Decode Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";

        //  Close the used classes
        predicterDec.closeStreams();

        //        TESTING
        //  Test all the pixels for all the frames of the decoded video against the original video
        cout << "\n ------------ Check Video ------------ \n";

        //  Reopen the original video
        video = cv::VideoCapture(videoLocation);

        cv::Mat originalFrame;
        bool readOriginal, readDecoded;
        int frameIndex = 1;

        //  Search every frame in the vector of frames
        for (cv::Mat decodedFrame : decodedVideo)
        {
            readOriginal = video.read(originalFrame);
            cout << " -> CHECKING Frame: " << frameIndex << "\n";
            cout << "\e[A";
            cout << "\r";

            //  Decoded video still has frames but the original does not (should not happen)
            if (!readOriginal)
            {
                cout << "ERROR! Tried reading non existent frame from the original video!\n";
                return;
            }

            //  For every row of pixels
            for (int i = 0; i < yFrameSize; i++)
            {
                //  For every column of pixels
                for (int j = 0; j < xFrameSize; j++)
                {
                    //  Test if the decoded pixel is the same as the original pixel
                    REQUIRE(originalFrame.at<cv::Vec3b>(i, j) == decodedFrame.at<cv::Vec3b>(i, j));
                }
            }
            frameIndex++;
        }
        cout << "\n -> OK              \n";
        //  All tests passed if we get here!
    }
}
