#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <iostream>

using namespace cv;

/**
 * @brief Main function for video processing
 * 
 * \n This function takes a video file path as an argument, opens the video file, and performs various operations on the video frames.
 * \n It allows the user to choose between RGB and YUV color modes and to set the speed of the video playback.
 * \n The processed frames are displayed in a window.
 * 
 * @param argc The number of command-line arguments
 * @param argv The command-line arguments. argv[1] should be the path to the video file.
 * 
 * @return Returns 0 if the function completes successfully. Returns -1 if the video file could not be opened.
 */
int main(int argc, char* argv[]) {

    //  Initial variables
    cv::VideoCapture cap;
    std::string videoPath = "20230912_140658.mp4";
    int speed;
    bool rgbMode = true;
    char userMode[5];
    int userSpeed;

    //  Get initial file as argument 
    if (argc > 0) {
        videoPath = argv[1];
    }

    //  Check if the file exists / can be open
    bool opened = cap.open(videoPath);
    if (!opened) {
        std::cerr << " Error: Video file not found or could not be opened." << std::endl;
        return -1;
    }

    //  Choose RGB mode (no) or YUV mode (yes)
    printf(" Choose YUV mode over RGB mode? (yes/no)\n          -> ");
    scanf("%s", userMode);

    if (!strcmp(userMode, "yes")) {
        rgbMode = false;
    }
    else {
        rgbMode = true;
    }

    //  Ask for the speed of the video playback (50% is half speed, 200% is doubled)
    printf(" What speed would you like the video to be in? (10 - 500) % \n          -> ");
    scanf("%d", &userSpeed);
    userSpeed = 30 * 100 / userSpeed ;

    //  Display all the frames
    while (true) {
        cv::Mat frame;
        cap >> frame;

        //  Check if this frame is the last
        if (frame.empty()) {
            std::cout << " End of video" << std::endl;
            break;
        }

        //  Select colour mode
        if (rgbMode) {
            //  Mostrar a frame em RGB
            cv::imshow("Video Player (RGB)", frame);
        } 
        else {
            //  Converter de RGB para YUV
            cv::Mat yuvFrame;
            cv::cvtColor(frame, yuvFrame, cv::COLOR_BGR2YUV);

            //  Mostrar a frame em YUV
            cv::imshow("Video Player (YUV)", yuvFrame);
        }

        //  Wait until the next frame (so video plays at correct framerate)
        int key = cv::waitKey(userSpeed);

        if (key == 'r') {
            rgbMode = true;
        } 
        else if (key == 'y') {
            rgbMode = false;
        } 
        else if (key == 27) {
            break;
        }
    }

    return 0;
}
