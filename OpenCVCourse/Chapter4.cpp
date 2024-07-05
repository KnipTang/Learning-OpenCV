#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//DRAWING SHAPES

int main()
{
	constexpr int waitTime = 0;

	cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));

	std::string path = "Resources/test.png";
	cv::Mat img2 = cv::imread(path);

	cv::circle(img, cv::Point(256, 256), 155, cv::Scalar(0, 69, 255), cv::FILLED);
	cv::rectangle(img, cv::Point(130, 226), cv::Point(382, 286), cv::Scalar(255, 255, 255), cv::FILLED);
	cv::line(img, cv::Point(130, 296), cv::Point(382, 296), cv::Scalar(255, 255, 255), 2);
	cv::line(img2, cv::Point(130, 296), cv::Point(382, 296), cv::Scalar(255, 255, 5), 2);

	cv::putText(img, "Murtaza's Workshop", cv::Point(137, 262), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0, 69, 255), 2);

	cv::imshow("Image", img);
	cv::imshow("Image2", img2);
	cv::waitKey(waitTime);
}