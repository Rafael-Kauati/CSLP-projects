#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>



void applyWatermark(cv::Mat& Image, const std::string& watermarkPath, int waitkey) {
    cv::Mat watermark = cv::imread(watermarkPath, cv::IMREAD_UNCHANGED);

    if (watermark.empty()) {
        std::cerr << "Erro: Não foi possível abrir ou encontrar a imagem da marca d'água." << std::endl;
        return;
    }

    // Resize the watermark if it's too large
    if (watermark.rows > Image.rows / 4 || watermark.cols > Image.cols / 4) {
        double scale = std::min(static_cast<double>(Image.rows) / (4 * watermark.rows), static_cast<double>(Image.cols) / (4 * watermark.cols));
        cv::resize(watermark, watermark, cv::Size(), scale, scale);
    }

    // Calculate the position of the watermark in the bottom-right corner
    cv::Point watermarkPosition(Image.cols - watermark.cols, Image.rows - watermark.rows);

    // Apply the watermark to the image
    cv::Mat imageROI = Image(cv::Rect(watermarkPosition.x, watermarkPosition.y, watermark.cols, watermark.rows));
    double alpha = 0.5; // Transparency of the watermark
    cv::addWeighted(imageROI, 1.0, watermark, alpha, 0., imageROI);

    cv::imshow("Image with Watermark", Image);
    cv::waitKey(waitkey);
}



void displayHistogram (cv::Mat& Image)
{
    std::vector<cv::Mat> channels;
    cv::split(Image, channels);

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

    cv::imshow("Histogram", histImage);
    cv::waitKey(0);
}


void applyBlur(cv::Mat& Image, int maxkernel) {
    int MAX_KERNEL_LENGTH = maxkernel;
    int DELAY_BLUR = 100;

    //Normal blur
    cv::Mat blurImg = Image.clone();

     for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
        cv::blur(blurImg, blurImg, cv::Size(i, i), cv::Point(-1,-1));
        cv::imshow("Gaussian blur effect", blurImg);
        cv::waitKey(DELAY_BLUR);
    }

    cv::Mat gaussianedBlurImage = Image.clone();

    //Gaussian blur
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
        cv::GaussianBlur(gaussianedBlurImage, gaussianedBlurImage, cv::Size(i, i), 0, 0);
        cv::imshow("Gaussian blur effect ", gaussianedBlurImage);
        cv::waitKey(DELAY_BLUR);
    }
}


void applySegmentation(cv::Mat& Image, int thresholdValue, int waitkey) {
    cv::Mat thresholded = Image.clone(); // Imagem thresholded

    // Aplicar thresholding manualmente
   for (int i = 0; i < Image.rows; ++i) {
    for (int j = 0; j < Image.cols; ++j) {
        // Extract RGB values
        uchar r = Image.at<cv::Vec3b>(i, j)[2]; // Red
        uchar g = Image.at<cv::Vec3b>(i, j)[1]; // Green
        uchar b = Image.at<cv::Vec3b>(i, j)[0]; // Blue

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
    cv::imshow("Thresholded Image", thresholded);
    cv::waitKey(waitkey);
}


void grayScaleConversion(cv::Mat& Image, int waitkey)
{
    int rows = Image.rows;
    int cols = Image.cols;
    cv::Mat grayscaleImage(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Extract RGB values  Update the VERSION argument <min> value or use a ...<max> suffix to tell
            uchar r = Image.at<cv::Vec3b>(i, j)[2]; // Red
            uchar g = Image.at<cv::Vec3b>(i, j)[1]; // Green
            uchar b = Image.at<cv::Vec3b>(i, j)[0]; // Blue

            // Convert RGB to grayscale
            uchar gray = static_cast<uchar>(0.299 * r + 0.587 * g + 0.114 * b);  // Grayscale intensity

            // Set grayscale value
            grayscaleImage.at<uchar>(i, j) = gray;
        }
    }
    cv::imshow("Grayscale Image", grayscaleImage);
    cv::waitKey(waitkey);

}


void applyHistogramEqualization(cv::Mat& Image, int waitkey)
{
    int rows = Image.rows;
    int cols = Image.cols;
    cv::Mat grayscaleImage(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Extract RGB values  Update the VERSION argument <min> value or use a ...<max> suffix to tell
            uchar r = Image.at<cv::Vec3b>(i, j)[2]; // Red
            uchar g = Image.at<cv::Vec3b>(i, j)[1]; // Green
            uchar b = Image.at<cv::Vec3b>(i, j)[0]; // Blue

            // Convert RGB to grayscale
            uchar gray = static_cast<uchar>(0.299 * r + 0.587 * g + 0.114 * b);  // Grayscale intensity

            // Set grayscale value
            grayscaleImage.at<uchar>(i, j) = gray;
        }
    }
    

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

    cv::imshow("Equalized Grayscale Image", equalizedImage);
    cv::waitKey(waitkey);
}


void applyYuV(cv::Mat& Image, int waitkey)
{
    int rows = Image.rows;
    int cols = Image.cols;

    cv::Mat yuvImage(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Extract RGB values
            uchar r = Image.at<cv::Vec3b>(i, j)[2]; // Red
            uchar g = Image.at<cv::Vec3b>(i, j)[1]; // Green
            uchar b = Image.at<cv::Vec3b>(i, j)[0]; // Blue

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
    cv::waitKey(waitkey);
}



int main(int argc, char* argv[]) {
    // Lógica para analisar os argumentos de linha de comando e determinar as operações a serem executadas
    std::string inputPath;
    std::string watermarkPath;
    bool shouldApplyWatermark = false;
    bool shouldCalculateHistogram = false;
    bool shouldApplyBlur = false;
    bool shouldApplySegmentation = false;
    bool shouldApplyGrayScaled = false;
    bool shouldApplyYuVConv = false;
    bool shouldApplyHistEq = false;

    int thresholdvalue = 0;
    int maxkernel = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--source" && i + 1 < argc) {
            inputPath = argv[i + 1];
            ++i;
        } else if (arg == "--watermark" && i + 1 < argc) {
            watermarkPath = argv[i + 1];
            shouldApplyWatermark = true;
            ++i;
        } else if (arg == "--histogram") {
            shouldCalculateHistogram = true;
        } else if (arg == "--blur" && i + 1 < argc) {
            shouldApplyBlur = true;
            maxkernel = std::stoi(argv[i + 1]);
            ++i;
        } else if (arg == "--segmentation" && i + 1 < argc) {
            shouldApplySegmentation = true;
            thresholdvalue = std::stoi(argv[i + 1]);
            ++i;
        } else if (arg == "--grayscaled") {
            shouldApplyGrayScaled = true;
            ++i;
        } else if (arg == "--YuV") {
            shouldApplyYuVConv = true;
            ++i;
        } else if (arg == "--HistEq") {
            shouldApplyHistEq = true;
            ++i;
        } else {
            std::cerr << "Argumento inválido: " << arg << std::endl;
            return 1;
        }
    }


    cv::Mat image;
    // Check if the input file is an image or a video
    std::string extension = inputPath.substr(inputPath.find_last_of(".") + 1);
    if (extension == "jpg" || extension == "png" || extension == "bmp" || extension == "ppm") {
        // The input file is an image
        image = cv::imread(inputPath);
        if (image.empty()) {
            std::cerr << "Erro: Não foi possível abrir ou encontrar a imagem." << std::endl;
            return 1;
        }
        
        // Process the image as before...
    } else if (extension == "mp4" || extension == "avi") {
        // The input file is a video
        cv::VideoCapture cap(inputPath);
        if (!cap.isOpened()) {
            std::cerr << "Erro: Não foi possível abrir o vídeo." << std::endl;
            return 1;
        }

        cv::Mat frame;
        while (cap.read(frame)) {
            
            if (shouldApplyWatermark) {
                applyWatermark(frame, watermarkPath, 10);

            }

            if (shouldApplyGrayScaled) {
                grayScaleConversion(frame ,10);
            }

            if (shouldApplyYuVConv) {
                applyYuV(frame,10);
            }

            if (shouldCalculateHistogram) {
                displayHistogram(frame);
            }

            if (shouldApplyBlur) {
                applyBlur(frame, maxkernel);
            }

            if (shouldApplySegmentation) {
                applySegmentation(frame, thresholdvalue,10);
            }

            if (shouldApplyHistEq) {
                applyHistogramEqualization(frame, 10);
            }

        }
    } else {
        std::cerr << "Erro: Formato de arquivo não suportado." << std::endl;
        return 1;
    }


    // Exibir a imagem resultante
    cv::imshow("Resultado", image);
    cv::waitKey(0);

    if (shouldApplyWatermark) {
        applyWatermark(image, watermarkPath,0);
    }

    if (shouldApplyGrayScaled) {
        grayScaleConversion(image,0);
    }

    if (shouldApplyYuVConv) {
        applyYuV(image,0);
    }

    if (shouldCalculateHistogram) {
        displayHistogram(image);
    }

    if (shouldApplyBlur) {
        applyBlur(image, maxkernel);
    }

    if (shouldApplySegmentation) {
        applySegmentation(image, thresholdvalue,0);
    }

    if (shouldApplyHistEq) {
        applyHistogramEqualization(image, 0);
    }


    return 0;
}
