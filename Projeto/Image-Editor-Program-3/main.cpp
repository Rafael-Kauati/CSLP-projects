#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

/**
 * @brief Function to solve the Deliverable 1, Program 3 Image Processment operations 
 * Everythin is done with the image (cv::Mat) variable, that represents the original image that will be processed with the code execution
 * For now you should change the global/relative path of the image that u want to be processed
*/

int main() {
    // Load the image
    cv::Mat image = cv::imread("/home/tk/UA/3-ano/cslp/curr-repo/CSLP-projects/Projeto/Image-Editor-Program-3/img.jpg");
    std::cout << "Image Type: " << image.type() << std::endl;


    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }


    /**
     * @brief a), "Include a watermark into an image" 
     * The watermark is choosed by the global/relative path of the image file
    */
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
    bool accumulate = true; // or false, depending on your requirement
    cv::Mat r_hist, g_hist, b_hist;

    cv::calcHist(&channels[2], 1, nullptr, cv::noArray(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&channels[1], 1, nullptr, cv::noArray(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&channels[0], 1, nullptr, cv::noArray(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

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
    
    //a)
    cv::imshow("Image with Watermark", image);
    cv::waitKey(0);

    //b)
    int rows = image.rows;
    int cols = image.cols;

    cv::Mat yuvImage(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Extract RGB values
            uchar r = image.at<cv::Vec3b>(i, j)[2]; // Red
            uchar g = image.at<cv::Vec3b>(i, j)[1]; // Green
            uchar b = image.at<cv::Vec3b>(i, j)[0]; // Blue

            // Convert RGB to YUV
            uchar y = static_cast<uchar>(0.299 * r + 0.587 * g + 0.114 * b);  // Luma (Y')
            uchar u = static_cast<uchar>(-0.14713 * r - 0.28886 * g + 0.436 * b + 128); // U
            uchar v = static_cast<uchar>(0.615 * r - 0.51499 * g - 0.10001 * b + 128); // V

            // Set YUV values
            yuvImage.at<cv::Vec3b>(i, j)[0] = y;
            yuvImage.at<cv::Vec3b>(i, j)[1] = u;
            yuvImage.at<cv::Vec3b>(i, j)[2] = v;
        }
    }



    cv::imshow("YUV Image", yuvImage);
    cv::waitKey(0);

    //c)
    cv::imshow("Histogram", histImage);
    cv::waitKey(0);

    //d)
    cv::Mat grayscaleImage(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Extract RGB values  Update the VERSION argument <min> value or use a ...<max> suffix to tell
            uchar r = image.at<cv::Vec3b>(i, j)[2]; // Red
            uchar g = image.at<cv::Vec3b>(i, j)[1]; // Green
            uchar b = image.at<cv::Vec3b>(i, j)[0]; // Blue

            // Convert RGB to grayscale
            uchar gray = static_cast<uchar>(0.299 * r + 0.587 * g + 0.114 * b);  // Grayscale intensity

            // Set grayscale value
            grayscaleImage.at<uchar>(i, j) = gray;
        }
    }

    //cv::imshow("Grayscale Image", grayscaleImage);
    //cv::waitKey(0);


    //e)
    // Calcular o histograma da imagem de entrada
    cv::Mat hist;
    int histsize = 256; // Número de bins no histograma
    float Range[] = {0, 256}; // Range do pixel no histograma
    const float* HistRange = {Range};
    cv::calcHist(&grayscaleImage, 1, 0, cv::Mat(), hist, 1, &histsize, &HistRange, true, false);

    // Normalizar o histograma acumulado
    // Normalizar e equalizar o histograma
    cv::Mat cumulativeHist = hist.clone();
    for (int i = 1; i < histsize; ++i) {
        cumulativeHist.at<float>(i) += cumulativeHist.at<float>(i - 1);
    }
    cumulativeHist /= cumulativeHist.at<float>(histsize - 1);
    cumulativeHist *= 255;

    // Aplicar a equalização ao mapa de intensidade original
    cv::Mat equalizedImage(grayscaleImage.size(), grayscaleImage.type());
    for (int i = 0; i < grayscaleImage.rows; ++i) {
        for (int j = 0; j < grayscaleImage.cols; ++j) {
            equalizedImage.at<uchar>(i, j) = cv::saturate_cast<uchar>(cumulativeHist.at<float>(grayscaleImage.at<uchar>(i, j)));
        }
    }

    // Mostrar a imagem original e a imagem equalizada
    cv::imshow("Default grayscaled image", grayscaleImage);
    cv::waitKey(0);

    cv::imshow("Equalized Grayscale Image", equalizedImage);
    cv::waitKey(0);




    //f)
    int MAX_KERNEL_LENGTH = 31;
    int DELAY_BLUR = 100;

    //Normal blur
    cv::Mat blurImg = image.clone();

     for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
        cv::blur(blurImg, blurImg, cv::Size(i, i), cv::Point(-1,-1));
        cv::imshow("Gaussian blur effect", blurImg);
        cv::waitKey(DELAY_BLUR);
    }

    cv::Mat gaussianedBlurImage = image.clone();

    //Gaussian blur
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
        cv::GaussianBlur(gaussianedBlurImage, gaussianedBlurImage, cv::Size(i, i), 0, 0);
        cv::imshow("Gaussian blur effect ", gaussianedBlurImage);
        cv::waitKey(DELAY_BLUR);
    }

    


   //g)

   // Threshold the image using a chosen threshold value
   int thresholdValue = 128; // Limiar de thresholding

    cv::Mat thresholded = image.clone(); // Imagem thresholded

    // Aplicar thresholding manualmente
   for (int i = 0; i < image.rows; ++i) {
    for (int j = 0; j < image.cols; ++j) {
        // Extract RGB values
        uchar r = image.at<cv::Vec3b>(i, j)[2]; // Red
        uchar g = image.at<cv::Vec3b>(i, j)[1]; // Green
        uchar b = image.at<cv::Vec3b>(i, j)[0]; // Blue

        // Aplicar thresholding para cada canal (R, G, B)
        uchar thresholdedR = (r > thresholdValue) ? 255 : 0;
        uchar thresholdedG = (g > thresholdValue) ? 255 : 0;
        uchar thresholdedB = (b > thresholdValue) ? 255 : 0;

        // Set valores thresholded nos canais R, G, B
        thresholded.at<cv::Vec3b>(i, j)[2] = thresholdedR;
        thresholded.at<cv::Vec3b>(i, j)[1] = thresholdedG;
        thresholded.at<cv::Vec3b>(i, j)[0] = thresholdedB;
    }
}



    // Display the original and thresholded images
    cv::imshow("Thresholded Image RGB", thresholded);
    cv::waitKey(0);
    //cv::imshow("Thresholded Image GrayScaled", thresholdImg2);
    //cv::waitKey(0);


    return 0;
}
