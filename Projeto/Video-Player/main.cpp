#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <iostream>

using namespace cv;
int main();

int main() {
    const std::string videoPath = "/home/tk/UA/3-ano/cslp/curr-repo/CSLP-projects/Projeto/Video-Player/20230912_140658.mp4";
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

        int key = cv::waitKey(15);

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
