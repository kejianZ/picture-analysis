#pragma once
#include "cv.h"
#include "opencv.hpp"
#include "highgui.h"
#include <iostream>


using namespace std;
using namespace cv;

class Tgraphcapturer
{
public:
	Tgraphcapturer(Mat filename);
	~Tgraphcapturer();
	cv::Mat img();
	//cv::Mat *r;
	void output();
	const int rows = 480;
	const int cols = 640;
private:
	cv::Mat a;
};

Tgraphcapturer::Tgraphcapturer(Mat filename)
{
	a = filename; //IMREAD_GRAYSCALE
}

cv::Mat Tgraphcapturer::img() {
	return a;
}

void Tgraphcapturer::output() {
	imwrite("result.png", a);
}

Tgraphcapturer::~Tgraphcapturer()
{
}