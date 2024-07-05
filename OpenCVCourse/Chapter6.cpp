#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//COLOR DETECTION
/*
*/
int main()
{
	constexpr int waitTime = 1;
	std::string path = "Resources/lambo.png";

	cv::Mat img = cv::imread(path);
	if (img.empty()) {
		std::cerr << "Could not read the image: " << path << std::endl;
		return 1;
	}

	cv::Mat imgHSV;
	cv::Mat mask;
	cv::Mat maskedAreaToColor;

	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	int hmin = 0;
	int smin = 0;
	int vmin = 0;
	int hmax = 255;
	int smax = 255;
	int vmax = 255;

	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
	cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
	cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
	cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true)
	{
		cv::Scalar lowestValue(hmin, smin, vmin);
		cv::Scalar HighestValue(hmax, smax, vmax);
		cv::inRange(imgHSV, lowestValue, HighestValue, mask);

		// Create a result image that will show the masked areas in color
		maskedAreaToColor = cv::Mat::zeros(img.size(), img.type());
		img.copyTo(maskedAreaToColor, mask);

		cv::imshow("Image", img);
		cv::imshow("Image HSV", imgHSV);
		cv::imshow("Image MASK", mask);
		cv::imshow("Result", maskedAreaToColor);

		cv::waitKey(waitTime);
	}

	return 0;
}

