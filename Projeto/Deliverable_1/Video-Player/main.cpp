#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <iostream>

using namespace cv;

/**
 * @brief Main function for video processing
 * 
 * This function takes a video file path as an argument, opens the video file, and performs various operations on the video frames.
 * It converts the frames from BGR to YUV, performs 4:2:2 and 4:2:0 subsampling, and converts the frames back to RGB.
 * The processed frames are displayed in separate windows.
 * 
 * @param argc The number of command-line arguments
 * @param argv The command-line arguments. argv[1] should be the path to the video file.
 * 
 * @return Returns 0 if the function completes successfully. Returns -1 if the number of command-line arguments is not 2 or if the video file could not be opened.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <video_file_path>" << std::endl;
        return -1;
    }

    const std::string videoPath = argv[1];
    cv::VideoCapture cap;
    bool opened = cap.open(videoPath);

    if (!opened) {
        std::cerr << "Error: Video file not found or could not be opened." << std::endl;
        return -1;
    }

    cv::Mat yuvFrame, rgbFrame;

    cv::Mat yuv;

    cv::Mat yuv444, yuv422, yuv420;

    

    while (true) {
    bool read = cap.read(yuvFrame);

    if (!read) {
        // No more frames to read
        break;
    }

    cv::cvtColor(yuvFrame, yuvFrame, cv::COLOR_BGR2YUV);

    // Show the frame in YUV
    cv::imshow("Video Player (YUV)", yuvFrame);
    cv::waitKey(5);

    yuv444 = yuvFrame.clone();
    yuv422 = yuvFrame.clone();
    yuv420 = yuvFrame.clone();

    // 4:2:2 subsampling
    cv::resize(yuv422, yuv422, cv::Size(), 0.5, 1, cv::INTER_LINEAR);
    cv::resize(yuv422, yuv422, yuvFrame.size(), 0, 0, cv::INTER_LINEAR);

    cv::imshow("Video Player (YUV mode 4:2:2)", yuv422);
    cv::waitKey(5);

    // 4:2:0 subsampling
    cv::resize(yuv420, yuv420, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
    cv::resize(yuv420, yuv420, yuvFrame.size(), 0, 0, cv::INTER_LINEAR);

    cv::imshow("Video Player (YUV mode 4:2:0)", yuv420);
    cv::waitKey(5);

    // Convert from YUV to RGB
    cv::cvtColor(yuvFrame, rgbFrame, cv::COLOR_YUV2BGR);

    // Show the frame in RGB
    cv::imshow("Video Player (RGB)", rgbFrame);
    cv::waitKey(5);

    if (cv::waitKey(20) == 27) { // Press 'Esc' to exit the loop
        std::cerr << "Video player terminated by user." << std::endl;
        break;
    }
}

    return 0;
}
