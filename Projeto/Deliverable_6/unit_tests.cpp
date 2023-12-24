/**
 * @file unit_tests.cpp
 * @brief Test case for Video Encoding and Decoding with Interframe Prediction.
 */

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"

#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include "Golomb/Golomb.cpp"
#include "HybridCodec/BitStream.h"
#include <chrono>
#include "HybridCodec/HybridCodec.cpp"
#include "VideoReader/VideoReader.cpp"

using namespace std;
using namespace cv;

/**
 * @defgroup HybridCodecTest Video Encoding/Decoding Test
 * @brief Test suite for the Hybrid Codec implementation.
 */

/**
 * @ingroup HybridCodecTest
 * @brief Complete Video (Array of Frames) Test Case.
 *
 * This test case covers the encoding and decoding of a video using the Hybrid Codec
 * with interframe prediction. It allows the user to select input parameters such as
 * search size, block size, and step size. The test includes measuring and printing the
 * time taken for encoding and decoding processes. Finally, it compares the pixels of
 * the original video with the decoded video.
 */
TEST_CASE("Video Encoding/Decoding")
{

    /**
     * @brief Pixel-by-Pixel Comparison.
     *
     * This section compares each pixel of the original video with the corresponding
     * pixel in the decoded video. It checks if the decoded video matches the original
     * video frame by frame.
     */
    SECTION("Complete Video (array of frames)")
    {

        cout << " ------------- ---------- ------------- \n";
        cout << " -- COMPLETE VIDEO ENCODING/DECODING -- \n";
        cout << " --    WITH INTERFRAME PREDICTION    -- \n";
        cout << " ------------- ---------- ------------- \n";

        //  Define the test variables here
        int m = 8;
        int blockSize = 8;
        int searchSize = 4;
        int frequency = 3;
        int stepSize = 4;

        //  File system locations
        string defaultVideoLocation = "TestFiles/ducks_11_frames.y4m";
        string videoLocation = "";
        string outputBinFile = "BinFiles/output.bin";
        string outputVidFile = "OutputFiles/output.mp4";
        string outputYUVFile = "OutputFiles/output.y4m";

        //  Ask for the file to read
        cout << "\n Please select the input video file: ";
        cout << "\n (empty for " << defaultVideoLocation << ") \n";
        cout << "        -=> ";
        getline(std::cin, videoLocation);
        ;

        if (videoLocation == "")
        {
            videoLocation = defaultVideoLocation;
        }

        string temp;
        //  Ask for the search size
        cout << "\n Please select the search size: ";
        cout << "\n (empty for " << searchSize << ") \n";
        cout << "        -=> ";
        getline(std::cin, temp);

        if (temp != "")
        {
            searchSize = stoi(temp);
        }

        //  Ask for the block size
        cout << "\n Please select the block size: ";
        cout << "\n (empty for " << blockSize << ") \n";
        cout << "        -=> ";
        getline(std::cin, temp);

        if (temp != "")
        {
            blockSize = stoi(temp);
        }

        //  Ask for the step size
        cout << "\n Please select the step size: ";
        cout << "\n (empty for " << stepSize << ") \n";
        cout << "        -=> ";
        getline(std::cin, temp);

        if (temp != "")
        {
            stepSize = stoi(temp);
        }

        //  Ask for the frequency of intra-frame coding
        cout << "\n Please select the intra-frame frquency: ";
        cout << "\n (empty for " << frequency << ") \n";
        cout << "        -=> ";
        getline(std::cin, temp);

        if (temp != "")
        {
            frequency = stoi(temp);
        }

        //  Open the input video capture

        VideoReader video(videoLocation);

        if (video.readError()) {
            cout << " ERROR: Cannot read video file!\n";
            return;
        }

        //  Calculate the video's metadata
        int xFrameSize = video.getFrameWidth();
        int yFrameSize = video.getFrameHeigth();
        int fps = video.getVideoFPS();

        //  Print all the final parameters
        cout << "\n ------------- Parameters ------------- \n";
        cout << " -> M = " << m << "\n";
        cout << " -> Block Size = " << blockSize << "\n";
        cout << " -> Search Size = " << searchSize << "\n";
        cout << " -> Frequency = " << frequency << "\n";
        cout << " -> Step Size = " << stepSize << "\n";
        cout << " -> Video = " << videoLocation << "\n";
        cout << " -> Video Size = " << xFrameSize << "x" << yFrameSize << "\n";
        cout << " -> Output Bin File = " << outputBinFile << "\n";
        cout << " -> Output Vid File = " << outputVidFile << "\n";
        cout << " -> Output Y4M File = " << outputYUVFile << "\n";

        //        ENCODING
        //  Instanciate the Hybrid Codec for encoding
        HybridCodec hybridEnc("", outputBinFile, blockSize, searchSize, frequency, stepSize);

        //  Write the parameters needed for all the classes
        cout << "\n ---------- Write Parameters ---------- \n";
        hybridEnc.writeParams(m, xFrameSize, yFrameSize, 1, fps, blockSize, searchSize, frequency);
        cout << " -> OK\n";

        //  Write the video itself to the file (and time the execution)
        cout << "\n ------------ Write Video ------------ \n";
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        hybridEnc.encodeVideo(video);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        cout << " -> Encode Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";

        //  Close the used classes
        hybridEnc.close();
        
        //  Instanciate the Hybrid Codec for decoding
        HybridCodec hybridDec(outputBinFile, "", blockSize, searchSize, frequency, stepSize);

        //  Read the parameters needed for all the classes
        cout << "\n ---------- Read Parameters ---------- \n";
        hybridDec.readParams();
        cout << " -> OK\n";

        //  Read the video itself from the file (and time the execution)
        cout << "\n ------------ Read Video ------------ \n";
        begin = std::chrono::steady_clock::now();

        hybridDec.decodeVideo(outputVidFile, outputYUVFile);

        end = std::chrono::steady_clock::now();
        cout << " -> Decode Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "\n";

        //  Close the used classes
        hybridDec.close();

        //  Test if the original y4m file is the same as the output y4m file
        cout << "\n ------------ Check File ------------ \n";

        //  Check if the two files are the same
        REQUIRE(VideoReader::compareFiles(outputYUVFile, videoLocation));

        //  All tests passed if we get here!
        cout << "\n -> OK            \n";
    }
}
