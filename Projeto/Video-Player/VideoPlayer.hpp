#ifndef VIDEO_PLAYER_HPP
#define VIDEO_PLAYER_HPP

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <iostream>

/**
 * @brief The VideoPlayer class encapsulates video playing functionality.
 * 
 * This class provides methods to play a video file in both YUV and RGB modes.
 */
class VideoPlayer {
public:
    /**
     * @brief Constructs a new VideoPlayer object.
     * 
     * @param videoPath The path to the video file to be played.
     */
    VideoPlayer(const std::string& videoPath);

    /**
     * @brief Destroys the VideoPlayer object and releases resources.
     */
    ~VideoPlayer();

    /**
     * @brief Starts playing the video in YUV and RGB modes.
     * 
     * This function reads frames from the video file, displays them in YUV mode,
     * converts them to RGB mode, and displays the frames again.
     */
    void play();

private:
    cv::VideoCapture cap; ///< OpenCV VideoCapture object to handle video input.
};

#endif // VIDEO_PLAYER_HPP
