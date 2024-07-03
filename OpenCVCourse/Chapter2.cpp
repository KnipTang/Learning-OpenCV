#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//BASIC FUNCTIONS

int main()
{
	constexpr int waitTime = 0;
	std::string path = "Resources/test.png";

	//Mat = matrix
	cv::Mat img = cv::imread(path);
	// Check if the image was loaded
	if (img.empty()) {
		std::cerr << "Could not read the image: " << path << std::endl;
		return 1;
	}

	cv::Mat imgGray;
	cv::Mat imgBlur;
	cv::Mat imgCanny;
	cv::Mat imgDialation;
	cv::Mat imgErodetion;

	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(img, imgBlur, cv::Size(3,3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDialation, kernel);
	cv::erode(imgDialation, imgErodetion, kernel);

	//Displays Image
	cv::imshow("Image", img);
	cv::imshow("Image Gray", imgGray);
	cv::imshow("Image Blur", imgBlur);
	cv::imshow("Image Canny", imgCanny);
	cv::imshow("Image Dilation", imgDialation);
	cv::imshow("Image Erode", imgErodetion);

	cv::waitKey(waitTime);
}