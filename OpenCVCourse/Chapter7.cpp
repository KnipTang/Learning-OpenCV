#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//SHAPE DETECTION

void GetContours(cv::Mat imgDialation, cv::Mat img)
{
	cv::findContours(imgDialation, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
}

int main()
{
	constexpr int waitTime = 0;
	std::string path = "Resources/shapes.png";

	cv::Mat img = cv::imread(path);
	if (img.empty()) {
		std::cerr << "Could not read the image: " << path << std::endl;
		return 1;
	}

	cv::Mat imgGray;
	cv::Mat imgBlur;
	cv::Mat imgCanny;
	cv::Mat imgDialation;
	cv::Mat imgErodetion;

	// Image Preprocessing
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 25, 75);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDialation, kernel);

	GetContours();

	cv::imshow("Image", img);
	cv::imshow("Image Gray", imgGray);
	cv::imshow("Image Blur", imgBlur);
	cv::imshow("Image Canny", imgCanny);
	cv::imshow("Image Dilation", imgDialation);
	cv::waitKey(waitTime);

	return 0;
}