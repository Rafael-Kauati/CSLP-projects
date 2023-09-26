#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <iostream>

int main() {
    // Load the main image
    cv::Mat image = cv::imread("/home/tk/UA/3-ano/cslp/curr-repo/CSLP-projects/Projeto/Image-Editor-Program-3/img.jpg");

    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    // Load the watermark image
    cv::Mat watermark = cv::imread("/home/tk/UA/3-ano/cslp/curr-repo/CSLP-projects/Projeto/Image-Editor-Program-3/wm.png");

    if (watermark.empty()) {
        std::cerr << "Error: Could not open or find the watermark image." << std::endl;
        return -1;
    }

    // Define the position to overlay the watermark (adjust as needed)
    cv::Point watermarkPosition(20, 40);

    // Overlay the watermark onto the main image
    for (int y = 0; y < watermark.rows; ++y) {
        for (int x = 0; x < watermark.cols; ++x) {
            cv::Vec3b pixel = watermark.at<cv::Vec3b>(y, x);

            // Check for a non-white pixel (you can adjust the threshold as needed)
            if (pixel[0] > 200 && pixel[1] > 200 && pixel[2] > 200) {
                continue; // Skip white pixels
            }

            // Overlay the pixel onto the main image
            int mainImageX = watermarkPosition.x + x;
            int mainImageY = watermarkPosition.y + y;

            if (mainImageX >= 0 && mainImageX < image.cols && mainImageY >= 0 && mainImageY < image.rows) {
                image.at<cv::Vec3b>(mainImageY, mainImageX) = pixel;
            }
        }
    }

    // Save the image with the watermark
    cv::imwrite("output_image_with_watermark.jpg", image);

    // Display the image with the watermark (optional)
    cv::imshow("Image with Watermark", image);
    cv::waitKey(0);

    return 0;
}