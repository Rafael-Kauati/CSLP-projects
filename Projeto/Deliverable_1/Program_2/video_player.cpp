#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/**
 * @brief Main function to read and display a video file.
 * This function reads a video file frame by frame using the VideoCapture class.
 * It displays each frame in a window called "MyVideo" until the 'esc' key is pressed.
 * 
 * @return 0 if successful, -1 otherwise
*/
int main() {

    std::string inpVideo = "inpVideo.mp4";

    //  Create the object of class video capture
    VideoCapture cap(inpVideo);
    
    if (!cap.isOpened()) {
        std::cout << "Cannot open the video file. \n";
        return -1;
    }

    //  Get the frames per seconds of the video
    double fps = cap.get(cv::CAP_PROP_POS_FRAMES);

    // cCreate a window called "MyVideo"
    namedWindow("Video_Window",WINDOW_AUTOSIZE);

    while(1) {
        // Mat object is a basic image container. frame is an object of Mat.
        Mat frame;

        //  Decode next frame
        if (!cap.read(frame)) {
            std::cout<<"\n Cannot read the video file. \n";
            break;
        }

        //  Show image
        imshow("A_good_name", frame);

        //  Wait for 'esc' key press to exit
        if(waitKey(30) == 27) { 
            break; 
        }
    }

    return 0;
}