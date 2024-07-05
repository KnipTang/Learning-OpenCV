#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//IMAGE

int main()
{
	constexpr int waitTime = 0;
	std::string path = "Resources/cards.jpg";

	cv::Mat img = cv::imread(path);
	if (img.empty()) {
		std::cerr << "Could not read the image: " << path << std::endl;
		return 1;
	}

	cv::Mat matrix;
	cv::Mat imgWarp;

	float w = 250;
	float h = 350;

	cv::Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };
	cv::Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, cv::Point(w, h));

	for (int i = 0; i < 4; i++)
	{
		cv::circle(img, src[i], 10, cv::Scalar(0, 0, 255), cv::FILLED);
	}

	cv::imshow("Image", img);
	cv::imshow("Image Warp", imgWarp);
	cv::waitKey(waitTime);

	return 0;
}