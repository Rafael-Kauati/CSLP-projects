#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

/**
 * @brief Applies a watermark to an image.
 * \n This function applies a watermark to an image by overlaying the watermark image on top of the original image, at the bottom-right.
 * \n The watermark image is resized if it is too large.
 *
 * @param Image The image to apply the watermark to.
 * @param watermarkPath The path to the watermark image.
 * @param waitkey The amount of time to wait after displaying the image.
 */

void applyWatermark(cv::Mat &Image, const std::string &watermarkPath, int waitkey)
{
    cv::Mat watermark = cv::imread(watermarkPath, cv::IMREAD_UNCHANGED);

    if (watermark.empty())
    {
        std::cerr << "Erro: Não foi possível abrir ou encontrar a imagem da marca d'água." << std::endl;
        return;
    }

    // Resize the watermark if it's too large
    if (watermark.rows > Image.rows / 4 || watermark.cols > Image.cols / 4)
    {
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

/**
 * @brief Displays the histogram of an image.
 * \n This function calculates and displays the histogram of an input image. It calculates histograms for each channel (red, green, and blue) and normalizes them.
 * \n Then, it creates an image to visualize the histograms and displays it.
 *
 * @param Image The image to calculate the histogram of.
 */
void displayHistogram(cv::Mat &Image)
{
    std::vector<cv::Mat> channels;
    cv::split(Image, channels);

    // Calculate histograms for each channel
    int histSize = 256;       // Number of bins
    float range[] = {0, 256}; // Range of pixel values
    const float *histRange = {range};
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

    for (int i = 1; i < histSize; i++)
    {
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

/**
 * @brief Applies a blur effect to an image.
 * \n This function applies a blur effect to an image by using normal blur and gaussian blur.
 * \n It uses the cv::blur and cv::GaussianBlur functions to apply the blur effect.
 *
 * @param Image The input image to apply the blur effect to.
 * @param maxkernel The maximum kernel size for the blur effect.
 */
void applyBlur(cv::Mat &Image, int maxkernel)
{
    int MAX_KERNEL_LENGTH = maxkernel;
    int DELAY_BLUR = 100;

    // Normal blur
    cv::Mat blurImg = Image.clone();

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        cv::blur(blurImg, blurImg, cv::Size(i, i), cv::Point(-1, -1));
        cv::imshow("Gaussian blur effect", blurImg);
        cv::waitKey(DELAY_BLUR);
    }

    cv::Mat gaussianedBlurImage = Image.clone();

    // Gaussian blur
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        cv::GaussianBlur(gaussianedBlurImage, gaussianedBlurImage, cv::Size(i, i), 0, 0);
        cv::imshow("Gaussian blur effect ", gaussianedBlurImage);
        cv::waitKey(DELAY_BLUR);
    }
}

/**
 * @brief Applies a segmentation effect to an image.
 * \n Applies segmentation to an image using manual thresholding.
 * \n It acesses each pixel in the image and applies thresholding to each channel (red, green, and blue).
 *
 * @param Image The input image to apply segmentation to.
 * @param thresholdValue The threshold value for segmentation.
 * @param waitkey The waitkey value for displaying the thresholded image.
 */
void applySegmentation(cv::Mat &Image, int thresholdValue, int waitkey)
{
    cv::Mat thresholded = Image.clone(); // Imagem thresholded

    // Aplicar thresholding manualmente
    for (int i = 0; i < Image.rows; ++i)
    {
        for (int j = 0; j < Image.cols; ++j)
        {
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

/**
* @brief Converts an image to grayscale.    
* \n This function converts an image to grayscale by extracting the RGB values of each pixel and calculating the grayscale intensity.
* \n The grayscale instensity is calculated using the formula: 0.299 * R + 0.587 * G + 0.114 * B, where R, G, and B are the RGB values of the pixel.
* \n The grayscale intensity is then set as the value of each channel (R, G, and B) of the pixel.
*
* @param Image The input image to convert to grayscale.
* @param waitkey The waitkey value for displaying the grayscale image.
*/

void grayScaleConversion(cv::Mat &Image, int waitkey)
{
    int rows = Image.rows;
    int cols = Image.cols;
    cv::Mat grayscaleImage(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // Extract RGB values  Update the VERSION argument <min> value or use a ...<max> suffix to tell
            uchar r = Image.at<cv::Vec3b>(i, j)[2]; // Red
            uchar g = Image.at<cv::Vec3b>(i, j)[1]; // Green
            uchar b = Image.at<cv::Vec3b>(i, j)[0]; // Blue

            // Convert RGB to grayscale
            uchar gray = static_cast<uchar>(0.299 * r + 0.587 * g + 0.114 * b); // Grayscale intensity

            // Set grayscale value
            grayscaleImage.at<uchar>(i, j) = gray;
        }
    }
    cv::imshow("Grayscale Image", grayscaleImage);
    cv::waitKey(waitkey);
}

/**
 * @brief Applies histogram equalization to an image.
 * This function applies histogram equalization to an image by calculating the histogram of the image, normalizing it, and equalizing it.
 * Then, it applies the equalization to the original image and displays the result.
 * 
 * @param Image The input image to apply histogram equalization to.
 * @param waitkey The waitkey value for displaying the equalized image.
*/
void applyHistogramEqualization(cv::Mat &Image, int waitkey)
{
    int rows = Image.rows;
    int cols = Image.cols;
    cv::Mat grayscaleImage(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // Extract RGB values  Update the VERSION argument <min> value or use a ...<max> suffix to tell
            uchar r = Image.at<cv::Vec3b>(i, j)[2]; // Red
            uchar g = Image.at<cv::Vec3b>(i, j)[1]; // Green
            uchar b = Image.at<cv::Vec3b>(i, j)[0]; // Blue

            // Convert RGB to grayscale
            uchar gray = static_cast<uchar>(0.299 * r + 0.587 * g + 0.114 * b); // Grayscale intensity

            // Set grayscale value
            grayscaleImage.at<uchar>(i, j) = gray;
        }
    }

    cv::Mat hist;
    int histsize = 256;       // Número de bins no histograma
    float Range[] = {0, 256}; // Range do pixel no histograma
    const float *HistRange = {Range};
    cv::calcHist(&grayscaleImage, 1, 0, cv::Mat(), hist, 1, &histsize, &HistRange, true, false);

    // Normalizar o histograma acumulado
    // Normalizar e equalizar o histograma
    cv::Mat cumulativeHist = hist.clone();
    for (int i = 1; i < histsize; ++i)
    {
        cumulativeHist.at<float>(i) += cumulativeHist.at<float>(i - 1);
    }
    cumulativeHist /= cumulativeHist.at<float>(histsize - 1);
    cumulativeHist *= 255;

    // Aplicar a equalização ao mapa de intensidade original
    cv::Mat equalizedImage(grayscaleImage.size(), grayscaleImage.type());
    for (int i = 0; i < grayscaleImage.rows; ++i)
    {
        for (int j = 0; j < grayscaleImage.cols; ++j)
        {
            equalizedImage.at<uchar>(i, j) = cv::saturate_cast<uchar>(cumulativeHist.at<float>(grayscaleImage.at<uchar>(i, j)));
        }
    }

    cv::imshow("Equalized Grayscale Image", equalizedImage);
    cv::waitKey(waitkey);
}

/**
 * @brief Converts a RGB image to YUV.
 * 
 * This function converts a RGB image to YUV by extracting the RGB values of each pixel and calculating the YUV values.
 * The YUV values are calculated using the formulas:
 * \n Y = 0.299 * R + 0.587 * G + 0.114 * B
 * \n U = -0.14713 * R - 0.28886 * G + 0.436 * B + 128
 * \n V = 0.615 * R - 0.51499 * G - 0.10001 * B + 128
 * \n where R, G, and B are the RGB values of the pixel.
 * 
 * @param Image The input image to convert to YUV.
 * @param waitkey The waitkey value for displaying the YUV image.
*/
void applyYuV(cv::Mat &Image, int waitkey)
{
    int rows = Image.rows;
    int cols = Image.cols;

    cv::Mat yuvImage(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // Extract RGB values
            uchar r = Image.at<cv::Vec3b>(i, j)[2]; // Red
            uchar g = Image.at<cv::Vec3b>(i, j)[1]; // Green
            uchar b = Image.at<cv::Vec3b>(i, j)[0]; // Blue

            // Convert RGB to YUV
            uchar y = static_cast<uchar>(0.299 * r + 0.587 * g + 0.114 * b);            // Luma (Y')
            uchar u = static_cast<uchar>(-0.14713 * r - 0.28886 * g + 0.436 * b + 128); // U
            uchar v = static_cast<uchar>(0.615 * r - 0.51499 * g - 0.10001 * b + 128);  // V

            // Set YUV values
            yuvImage.at<cv::Vec3b>(i, j)[0] = y;
            yuvImage.at<cv::Vec3b>(i, j)[1] = u;
            yuvImage.at<cv::Vec3b>(i, j)[2] = v;
        }
    }

    cv::imshow("YUV Image", yuvImage);
    cv::waitKey(waitkey);
}

/**
 * @brief Main function for image processing.
 * This function analyzes the command line arguments and performs various image processing operations based on the provided arguments.
 * 
 * @param argc The number of command line arguments.
 * @param argv An array of command line arguments.
 * @return 0 if the program executed successfully, 1 otherwise.
 * @details The main function takes in command line arguments to determine the operations to be performed on the input image or video. The supported arguments are as follows:
 * \n    --source <inputPath>: Specifies the path to the input image or video file.
 * \n    --watermark <watermarkPath>: Specifies the path to the watermark image file. If provided, the watermark will be applied to the image or video.
 * \n    --histogram: Calculates and displays the histogram of the image or video.
 * \n    --blur <maxkernel>: Applies a blur effect to the image or video using both normal blur and Gaussian blur. The maxkernel parameter specifies the maximum kernel size for the blur effect.
 * \n    --segmentation <thresholdvalue>: Applies segmentation to the image or video using manual thresholding. The thresholdvalue parameter specifies the threshold value for segmentation.
 * \n    --grayscaled: Converts the image or video to grayscale.
 * \n    --YuV: Applies the YUV color space conversion to the image or video.
 * \n    --HistEq: Applies histogram equalization to the grayscale image or video.
 * \n The main function first parses the command line arguments and sets the corresponding flags and parameters. It then checks the file extension of the input file to determine if it is an image or a video. If it is an image, the image is read using OpenCV's imread function. If it is a video, the video is read using OpenCV's VideoCapture class and processed frame by frame.
 * \n For each frame, the specified operations are applied in the following order:
 * \n    If the --watermark flag is set, the watermark is applied to the frame using the applyWatermark function.
 * \n    If the --grayscaled flag is set, the frame is converted to grayscale using the grayScaleConversion function.
 * \n    If the --YuV flag is set, the YUV color space conversion is applied to the frame using the applyYuV function.
 * \n    If the --histogram flag is set, the histogram of the frame is calculated and displayed using the displayHistogram function.
 * \n    If the --blur flag is set, a blur effect is applied to the frame using both normal blur and Gaussian blur with the specified maxkernel using the applyBlur function.
 * \n    If the --segmentation flag is set, segmentation is applied to the frame using manual thresholding with the specified thresholdvalue using the applySegmentation function.
 * \n    If the --HistEq flag is set, histogram equalization is applied to the grayscale frame using the applyHistogramEqualization function.
 * \n After processing all frames, the resulting image or video is displayed using OpenCV's imshow function. If the --watermark flag is set, the watermark is also applied to the resulting image using the applyWatermark function. Finally, the program waits for a key press and returns 0 if the program executed successfully. 
*/
int main(int argc, char *argv[])
{
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

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--source" && i + 1 < argc)
        {
            inputPath = argv[i + 1];
            ++i;
        }
        else if (arg == "--watermark" && i + 1 < argc)
        {
            watermarkPath = argv[i + 1];
            shouldApplyWatermark = true;
            ++i;
        }
        else if (arg == "--histogram")
        {
            shouldCalculateHistogram = true;
        }
        else if (arg == "--blur" && i + 1 < argc)
        {
            shouldApplyBlur = true;
            maxkernel = std::stoi(argv[i + 1]);
            ++i;
        }
        else if (arg == "--segmentation" && i + 1 < argc)
        {
            shouldApplySegmentation = true;
            thresholdvalue = std::stoi(argv[i + 1]);
            ++i;
        }
        else if (arg == "--grayscaled")
        {
            shouldApplyGrayScaled = true;
            ++i;
        }
        else if (arg == "--YuV")
        {
            shouldApplyYuVConv = true;
            ++i;
        }
        else if (arg == "--HistEq")
        {
            shouldApplyHistEq = true;
            ++i;
        }
        else
        {
            std::cerr << "Argumento inválido: " << arg << std::endl;
            return 1;
        }
    }

    cv::Mat image;
    // Check if the input file is an image or a video
    std::string extension = inputPath.substr(inputPath.find_last_of(".") + 1);
    if (extension == "jpg" || extension == "png" || extension == "bmp" || extension == "ppm")
    {
        // The input file is an image
        image = cv::imread(inputPath);
        if (image.empty())
        {
            std::cerr << "Erro: Não foi possível abrir ou encontrar a imagem." << std::endl;
            return 1;
        }

        // Process the image as before...
    }
    else if (extension == "mp4" || extension == "avi")
    {
        // The input file is a video
        cv::VideoCapture cap(inputPath);
        if (!cap.isOpened())
        {
            std::cerr << "Erro: Não foi possível abrir o vídeo." << std::endl;
            return 1;
        }

        cv::Mat frame;
        while (cap.read(frame))
        {

            if (shouldApplyWatermark)
            {
                applyWatermark(frame, watermarkPath, 10);
            }

            if (shouldApplyGrayScaled)
            {
                grayScaleConversion(frame, 10);
            }

            if (shouldApplyYuVConv)
            {
                applyYuV(frame, 10);
            }

            if (shouldCalculateHistogram)
            {
                displayHistogram(frame);
            }

            if (shouldApplyBlur)
            {
                applyBlur(frame, maxkernel);
            }

            if (shouldApplySegmentation)
            {
                applySegmentation(frame, thresholdvalue, 10);
            }

            if (shouldApplyHistEq)
            {
                applyHistogramEqualization(frame, 10);
            }
        }
    }
    else
    {
        std::cerr << "Erro: Formato de arquivo não suportado." << std::endl;
        return 1;
    }

    // Exibir a imagem resultante
    cv::imshow("Resultado", image);
    cv::waitKey(0);

    if (shouldApplyWatermark)
    {
        applyWatermark(image, watermarkPath, 0);
    }

    if (shouldApplyGrayScaled)
    {
        grayScaleConversion(image, 0);
    }

    if (shouldApplyYuVConv)
    {
        applyYuV(image, 0);
    }

    if (shouldCalculateHistogram)
    {
        displayHistogram(image);
    }

    if (shouldApplyBlur)
    {
        applyBlur(image, maxkernel);
    }

    if (shouldApplySegmentation)
    {
        applySegmentation(image, thresholdvalue, 0);
    }

    if (shouldApplyHistEq)
    {
        applyHistogramEqualization(image, 0);
    }

    return 0;
}
