#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


/////////////////  Images  //////////////////////

void main() {

    std::string path = "Resources/test.png";
    cv::Mat img = cv::imread(path);
    cv::imshow("Image", img);
    cv::waitKey(0);

}