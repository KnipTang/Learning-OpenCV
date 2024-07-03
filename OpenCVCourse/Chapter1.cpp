#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//IMAGE
/*
void main()
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

	//Displays Image
	cv::imshow("Image", img);

	cv::waitKey(waitTime);
}
*/



//VIDEO
/*
int main()
{
	constexpr int waitTime = 1;
	std::string path = "Resources/test_video.mp4";
	cv::VideoCapture cap(path);
	if (!cap.isOpened()) {
		std::cerr << "Error: Could not open the video file." << std::endl;
		return -1;
	}

	cv::Mat currentFrame;

	while (true)
	{
		bool isSuccess = cap.read(currentFrame);
		if (!isSuccess || currentFrame.empty()) {
			std::cerr << "Error: Failed to read the frame." << std::endl;
			break;
		}

		//Displays Image
		cv::imshow("Image", currentFrame);

		int key = cv::waitKey(waitTime);
		if (key == 'q' || key == 27) // 'q' or ESC key
			break;
	}

	cap.release();
	cv::destroyAllWindows();

	return 0;
}
*/



//WEBCAM
/*
*/
int main()
{
	constexpr int waitTime = 1;
	constexpr int cameraID = 0;
	cv::VideoCapture cap(cameraID);
	if (!cap.isOpened()) {
		std::cerr << "Error: Could not open the video file." << std::endl;
		return -1;
	}

	cv::Mat currentFrame;

	while (true)
	{
		bool isSuccess = cap.read(currentFrame);
		if (!isSuccess || currentFrame.empty()) {
			std::cerr << "Error: Failed to read the frame." << std::endl;
			break;
		}

		//Displays Image
		cv::imshow("Image", currentFrame);

		int key = cv::waitKey(waitTime);
		if (key == 'q' || key == 27) // 'q' or ESC key
			break;
	}

	cap.release();
	cv::destroyAllWindows();

	return 0;
}