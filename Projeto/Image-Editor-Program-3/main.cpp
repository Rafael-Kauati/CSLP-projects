#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // Load the image
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

    // Define the position of the watermark in the img 
    cv::Point watermarkPosition(20, 40);

    // Pos the watermark onto the main image
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

    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // Calculate histograms for each channel
    int histSize = 256; // Number of bins
    float range[] = {0, 256}; // Range of pixel values
    const float* histRange = {range};
    bool uniform = true;
    bool accumulate = false;
    cv::Mat b_hist, g_hist, r_hist;

    cv::calcHist(&channels[0], 1, nullptr, cv::noArray(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&channels[1], 1, nullptr, cv::noArray(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&channels[2], 1, nullptr, cv::noArray(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    cv::normalize(b_hist, b_hist, 0, 1, cv::NORM_MINMAX);

    cv::normalize(g_hist, g_hist, 0, 1, cv::NORM_MINMAX);
    cv::normalize(r_hist, r_hist, 0, 1, cv::NORM_MINMAX);

    int histWidth = 512;
    int histHeight = 400;
    cv::Mat histImage(histHeight, histWidth, CV_8UC3, cv::Scalar(255, 255, 255));

    int binWidth = cvRound((double)histWidth / histSize);

    for (int i = 1; i < histSize; i++) {
        cv::line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(b_hist.at<float>(i - 1) * histHeight)),

                 cv::Point(binWidth * i, histHeight - cvRound(b_hist.at<float>(i) * histHeight)),
                 cv::Scalar(255, 0, 0), 2, 8, 0);
        cv::line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(g_hist.at<float>(i - 1) * histHeight)),
        
                 cv::Point(binWidth * i, histHeight - cvRound(g_hist.at<float>(i) * histHeight)),
                 cv::Scalar(0, 255, 0), 2, 8, 0);
        cv::line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(r_hist.at<float>(i - 1) * histHeight)),
                 cv::Point(binWidth * i, histHeight - cvRound(r_hist.at<float>(i) * histHeight)),
                 cv::Scalar(0, 0, 255), 2, 8, 0);
    }

    cv::imshow("Image with Watermark", image);
    cv::waitKey(0);

    cv::imshow("Histogram", histImage);
    cv::waitKey(0);

    return 0;
}
