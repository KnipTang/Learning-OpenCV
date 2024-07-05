
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

	cv::CascadeClassifier faceCascade;
	if (!faceCascade.load("Resources/haarcascade_frontalface_default.xml")) {
		std::cerr << "XML file not loaded" << std::endl;
		return 1;
	}

	while (true)
	{
		bool isSuccess = cap.read(currentFrame);
		if (!isSuccess || currentFrame.empty()) {
			std::cerr << "Error: Failed to read the frame." << std::endl;
			break;
		}

		std::vector<cv::Rect> faces;
		faceCascade.detectMultiScale(currentFrame, faces, 1.1, 10);

		if (faces.size() <= 0) {
			cv::GaussianBlur(currentFrame, currentFrame, cv::Size(99, 99), 50);
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
				cv::GaussianBlur(faceROI, faceROI, cv::Size(99, 99), 50);
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