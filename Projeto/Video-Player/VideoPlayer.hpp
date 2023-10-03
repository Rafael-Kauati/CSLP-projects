#ifndef VIDEO_PLAYER_HPP
#define VIDEO_PLAYER_HPP

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <iostream>

/**
 * @brief The VideoPlayer class encapsulates video playing functionality.
 * 
 * This class provides methods to play a video file, switch between RGB and YUV modes,
 * and display frames from the video.
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
     * @brief Starts playing the video and allows switching between RGB and YUV modes.
     * 
     * This function continuously reads frames from the video file, converts them to YUV
     * format if not in RGB mode, and displays the frames.
     */
    void play();

private:
    cv::VideoCapture cap; ///< OpenCV VideoCapture object to handle video input.
    bool rgbMode; ///< A flag indicating whether the video is displayed in RGB mode or YUV mode.
};

#endif // VIDEO_PLAYER_HPP
