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
 
    bool rgbMode = false;

    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cout << "End of video" << std::endl;
            break;
        }

        if (rgbMode) {
            cv::imshow("Video Player (RGB)", frame);
        } else {
            // Converter de RGB para YUV
            cv::Mat yuvFrame;
            cv::cvtColor(frame, yuvFrame, cv::COLOR_BGR2YUV);

            // Mostrar o frame em YUV
            cv::imshow("Video Player (YUV)", yuvFrame);
        }

        int key = cv::waitKey(1);

        if (key == 'r') {
            rgbMode = true;
        } else if (key == 'y') {
            rgbMode = false;
        } else if (key == 27) {
            break;
        }
    }

    return 0;
}
