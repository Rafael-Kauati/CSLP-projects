#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include "Golomb.cpp"
#include "BitStream.h"
#include <chrono>
#include "HybridCodec.cpp"

using namespace std;
using namespace cv;

TEST_CASE("Video Encoding/Decoding") {
    SECTION("Complete Video (array of frames)") {

        cout << " ------------- ---------- ------------- \n";
        cout << " -- COMPLETE VIDEO ENCODING/DECODING -- \n";
        cout << " --    WITH INTERFRAME PREDICTION    -- \n";
        cout << " ------------- ---------- ------------- \n";
        int m = 8;
        int blockSize = 8;
        int searchSize = 16;
        int frequency = 6;

        string defaultVideoLocation = "testVideo.mp4";
        string videoLocation = "";
        string outputBinFile = "output.bin";
        string outputVidFile = "output.mp4";

        cout << "\n Please select the input video file: ";
        cout << "\n (empty for TestFiles/testVideo.mp4) \n";
        cout << "        -=> ";
        getline(std::cin, videoLocation);;

        if (videoLocation == "") {
            videoLocation = defaultVideoLocation;
        }

        cv::VideoCapture video(videoLocation);

        if (!video.isOpened()) {
            cout << " ERROR: Cannot read video file!\n";
            return;
        }

        int xFrameSize = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
        int yFrameSize = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
        int numFrames = (int)video.get(cv::CAP_PROP_FRAME_COUNT);
        int fps = (int)video.get(cv::CAP_PROP_FPS);

        cout << "\n ------------- Parameters ------------- \n";
        cout << " -> M = " << m << "\n";
        cout << " -> Block Size = " << blockSize << "\n";
        cout << " -> Search Size = " << searchSize << "\n";
        cout << " -> Frequency = " << frequency << "\n";
        cout << " -> Video = " << videoLocation << "\n";
        cout << " -> Video Size = " << xFrameSize << "x" << yFrameSize << "\n";
        cout << " -> Output Bin File = " << outputBinFile << "\n";
        cout << " -> Output Vid File = " << outputVidFile << "\n";

        HybridCodec hybridEnc("", outputBinFile, blockSize, searchSize, frequency);

        cout << "\n ---------- Write Parameters ---------- \n";
        hybridEnc.writeParams(m, xFrameSize, yFrameSize, 1, numFrames, fps);
        cout << " -> OK\n";

        cout << "\n ------------ Write Video ------------ \n";
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        hybridEnc.writeVideo(video);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        cout << " -> Encode Time: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "\n";
        hybridEnc.close();


        HybridCodec hybridDec(outputBinFile, "");

        cout << "\n ---------- Read Parameters ---------- \n";
        hybridDec.readParams();
        cout << " -> OK\n";

        cout << "\n ------------ Read Video ------------ \n";
        begin = std::chrono::steady_clock::now();

        vector<cv::Mat> decodedVideo = hybridDec.readVideo(outputVidFile);

        end = std::chrono::steady_clock::now();
        cout << " -> Encode Time: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "\n";

        hybridDec.close();

        cout << "\n ------------ Check Video ------------ \n";

        //  Reopen the original video
        video = cv::VideoCapture(videoLocation);

        cv::Mat originalFrame;
        bool readOriginal, readDecoded;
        int frameIndex = 1;

        for(cv::Mat decodedFrame : decodedVideo) {
            readOriginal = video.read(originalFrame);
            cout << " -> CHECKING Frame: " << frameIndex << "\n";
            cout << "\e[A";
            cout << "\r";

            //  Last frame has been read
            if (!readOriginal) {
            cout << "ERROR! Tried reading non existent frame from the original video!\n";
            return;
            }

            //  For every row
            for (int i = 0; i < yFrameSize; i++) {
                //  For every column
                for (int j = 0; j < xFrameSize; j++) {
                    REQUIRE(originalFrame.at<cv::Vec3b>(i, j) == decodedFrame.at<cv::Vec3b>(i, j));
                }
            }
            frameIndex++;
        }
        cout << "\n -> OK\n";
    }
}
