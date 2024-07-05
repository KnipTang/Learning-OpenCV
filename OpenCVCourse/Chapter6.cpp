#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//COLOR DETECTION
/*
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

	// Get the original resolution of the webcam
	int frameWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int frameHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	//float scaleFactor = 1.0;
	//int scaledWidth = static_cast<int>(frameWidth * scaleFactor);
	//int scaledHeight = static_cast<int>(frameHeight * scaleFactor);
	//bool scaleDirty = false;

	std::cout << "Original Webcam Resolution: " << frameWidth << "x" << frameHeight << std::endl;

	cv::Mat currentFrame;
	cv::Mat imgHSV;
	cv::Mat mask;
	cv::Mat maskedAreaToColor;

	int hmin = 0;
	int smin = 0;
	int vmin = 0;
	int hmax = 255;
	int smax = 255;
	int vmax = 255;

	cv::namedWindow("Trackbars", (640, 300));
	cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
	cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
	cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
	cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);
	cv::createTrackbar("frameWidth", "Trackbars", &frameWidth, 4000);
	cv::createTrackbar("frameHeight", "Trackbars", &frameHeight, 4000);
	//cv::createTrackbar("Scale Factor", "Trackbars", nullptr, 1000, [](int value, void* userdata) {
	//	float* scaleFactorPtr = static_cast<float*>(userdata);
	//	*scaleFactorPtr = static_cast<float>(value) / 1000.0f;
	//	}, &scaleFactor);

	while (true)
	{
		bool isSuccess = cap.read(currentFrame);
		if (!isSuccess || currentFrame.empty()) {
			std::cerr << "Error: Failed to read the frame." << std::endl;
			break;
		}

		cv::cvtColor(currentFrame, imgHSV, cv::COLOR_BGR2HSV);

		cv::Scalar lowestValue(hmin, smin, vmin);
		cv::Scalar HighestValue(hmax, smax, vmax);
		cv::inRange(imgHSV, lowestValue, HighestValue, mask);

		// Create a result image that will show the masked areas in color
		maskedAreaToColor = cv::Mat::zeros(currentFrame.size(), currentFrame.type());
		currentFrame.copyTo(maskedAreaToColor, mask);

		//if (scaleDirty)
		//{
		//	scaleFactor = static_cast<float>(frameWidth) / 100.0f; // Convert scale trackbar value to percentage
		//	scaledWidth = static_cast<int>(frameWidth * scaleFactor);
		//	scaledHeight = static_cast<int>(frameHeight * scaleFactor);
		//
		//	scaleDirty = false;
		//}

		cv::resize(currentFrame, currentFrame, cv::Size(frameWidth, frameHeight));
		cv::resize(imgHSV, imgHSV, cv::Size(frameWidth, frameHeight));
		cv::resize(mask, mask, cv::Size(frameWidth, frameHeight));
		cv::resize(maskedAreaToColor, maskedAreaToColor, cv::Size(frameWidth, frameHeight));

		//Displays Image
		cv::imshow("Image", currentFrame);
		cv::imshow("Image HSV", imgHSV);
		cv::imshow("Image MASK", mask);
		cv::imshow("Result", maskedAreaToColor);

		int key = cv::waitKey(waitTime);
		if (key == 'q' || key == 27) // 'q' or ESC key
			break;
	}

	cap.release();
	cv::destroyAllWindows();

	return 0;
}