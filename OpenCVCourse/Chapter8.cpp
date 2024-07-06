
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

//FACE DETECTION
/*
int main()
{
	constexpr int waitTime = 0;
	std::string path = "Resources/test.png";

	cv::Mat img = cv::imread(path);
	if (img.empty()) {
		std::cerr << "Could not read the image: " << path << std::endl;
		return 1;
	}

    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load("Resources/haarcascade_frontalface_default.xml")) {
        std::cerr << "XML file not loaded" << std::endl;
        return 1;
    }

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    for (const auto& face : faces) {
        cv::Mat faceROI = img(face);
        cv::GaussianBlur(faceROI, faceROI, cv::Size(51, 51), 50);
    }

	cv::imshow("Image", img);
	cv::waitKey(waitTime);

	return 0;
}
*/


//WEBCAM
/*
*/
void onChangeBlurLevel(int value, void* userData) {
	// Ensure blur level is odd
	if (value % 2 == 0) {
		value = std::max(value - 1, 1); // Set to nearest odd number
		cv::setTrackbarPos("Blur Level", "Trackbars", value);
	}
}

int main()
{
	constexpr int waitTime = 1;
	constexpr int cameraID = 0;
	constexpr double scaleFactor = 2;

	cv::VideoCapture cap(cameraID);
	if (!cap.isOpened()) {
		std::cerr << "Error: Could not open the video file." << std::endl;
		return -1;
	}

	cv::Mat currentFrame;
	cv::Mat faceROI;
	cv::Mat imgHSV;
	cv::Mat mask;

	cv::CascadeClassifier faceCascade;
	if (!faceCascade.load("Resources/haarcascade_frontalface_default.xml")) {
		std::cerr << "XML file not loaded" << std::endl;
		return 1;
	}

	cv::CascadeClassifier eyeCascade;
	if (!eyeCascade.load("Resources/haarcascade_eye_tree_eyeglasses.xml")) {
		std::cerr << "Error: Could not load eye cascade." << std::endl;
		return -1;
	}

	std::vector<cv::Rect> eyes;

	int blurLevel = 99;

	int frameCount = 0;
	int frameInterval = 10;

	int hmin = 0;
	int smin = 0;
	int vmin = 0;
	int hmax = 255;
	int smax = 255;
	int vmax = 255;

	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("Blur Level", "Trackbars", &blurLevel, 99, onChangeBlurLevel);
	cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
	cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
	cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
	cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true)
	{
		bool isSuccess = cap.read(currentFrame);
		if (!isSuccess || currentFrame.empty()) {
			std::cerr << "Error: Failed to read the frame." << std::endl;
			break;
		}

		//cv::cvtColor(currentFrame, imgHSV, cv::COLOR_BGR2HSV);
		//
		//cv::Scalar lowestValue(hmin, smin, vmin);
		//cv::Scalar HighestValue(hmax, smax, vmax);
		//cv::inRange(imgHSV, lowestValue, HighestValue, mask);
		//
		//// Create a result image that will show the masked areas in color
		//currentFrame = cv::Mat::zeros(currentFrame.size(), currentFrame.type());
		//currentFrame.copyTo(currentFrame, mask);

		/*
		frameCount++;
		*/


			cv::Mat gray;
			cv::cvtColor(currentFrame, gray, cv::COLOR_BGR2GRAY);
			cv::equalizeHist(gray, gray);

			// Detect eyes
			eyes.clear(); // Clear previous detections
			eyeCascade.detectMultiScale(gray, eyes);

			// Draw rectangles around detected eyes
			for (const auto& eye : eyes) {
				cv::rectangle(currentFrame, eye, cv::Scalar(0, 255, 0), 2);
			}
		
		std::vector<cv::Rect> faces;
		faceCascade.detectMultiScale(currentFrame, faces, 1.1, 10);

		if (faces.size() <= 0) {
			cv::GaussianBlur(currentFrame, currentFrame, cv::Size(blurLevel, blurLevel), 50);
		}
		else
		{
			for (const auto& face : faces) {
				// Calculate the new, scaled rectangle
				int newWidth = static_cast<int>(face.width * scaleFactor);
				int newHeight = static_cast<int>(face.height * scaleFactor);
				int newX = std::max(0, face.x - (newWidth - face.width) / 2);
				int newY = std::max(0, face.y - (newHeight - face.height) / 2);
				newWidth = std::min(newWidth, currentFrame.cols - newX);
				newHeight = std::min(newHeight, currentFrame.rows - newY);
		
				cv::Rect enlargedFace(newX, newY, newWidth, newHeight);
		
				faceROI = currentFrame(enlargedFace);
				cv::GaussianBlur(faceROI, faceROI, cv::Size(blurLevel, blurLevel), 50);
			}
		}

		cv::imshow("Image", currentFrame);

		int key = cv::waitKey(waitTime);
		if (key == 'q' || key == 27) // 'q' or ESC key
			break;
	}

	cap.release();
	cv::destroyAllWindows();

	return 0;
}