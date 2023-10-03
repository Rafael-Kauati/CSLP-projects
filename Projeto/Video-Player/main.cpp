#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <iostream>

using namespace cv;

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

    while (cap.read(yuvFrame)) {
        // Mostrar o frame em YUV
        cv::imshow("Video Player (YUV)", yuvFrame);
        cv::waitKey(10);

        // Converter de YUV para RGB
        cv::cvtColor(yuvFrame, rgbFrame, cv::COLOR_YUV2BGR);

        // Mostrar o frame em RGB
        cv::imshow("Video Player (RGB)", rgbFrame);
        cv::waitKey(10);

        if (cv::waitKey(20) == 27) { // Pressione 'Esc' para sair do loop
            std::cerr << "Video player terminated by user." << std::endl;
            break;
        }
    }

    return 0;
}
