#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//RESIZE AND CROP FUNCTIONS

int main()
{
	constexpr int waitTime = 0;
	std::string path = "Resources/test.png";

	cv::Mat img = cv::imread(path);
	if (img.empty()) {
		std::cerr << "Could not read the image: " << path << std::endl;
		return 1;
	}

	cv::Mat imgResize;
	cv::Mat imgCrop;

	cv::resize(img, imgResize, cv::Size(), 0.5, 0.5);
	
	//ROI = Region of Intrest
	cv::Rect roi(100, 100, 300, 250);
	imgCrop = img(roi);

	cv::imshow("Image", img);
	cv::imshow("Image Resize", imgResize);
	cv::imshow("Image Crop", imgCrop);

	cv::waitKey(waitTime);
}