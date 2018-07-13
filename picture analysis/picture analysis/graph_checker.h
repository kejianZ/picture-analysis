#pragma once
#include "cv.h"
#include "opencv.hpp"
#include "highgui.h"
#include <iostream>


using namespace std;
using namespace cv;

class Tgraphchecker
{
public:
	Tgraphchecker(const char* filename);
	~Tgraphchecker();
	//vector<vector<int>> result();
	int* result();
	int rows;
	int cols;
	int result_list[640 * 360];
	void deal_point(int* list);
private:
	cv::Mat a;
	

};

Tgraphchecker::Tgraphchecker(const char* filename)
{
	a = cv::imread(filename); //IMREAD_GRAYSCALE
	rows = a.rows;
	cols = a.cols;
}

//vector<vector<int>> Tgraphchecker::result()
//{
//	int col = 0;
//	int row = 0;
//	int value = 0;
//	vector<vector<int>> result(this->rows);
//	for (int i = 0; i < this->rows; i++)
//	{
//		result[i].resize(this->cols);
//	}
//	while (row < this->rows)
//	{
//		while (col < this->cols)
//		{
//			value = a.at<uchar>(row, col);
//			if (value != 0)
//			{
//				value = 1;
//			}
//			result[row][col] = value;
//			col++;
//		}
//		col = 0;
//		row++;
//	}
//	return result;
//}
int* Tgraphchecker::result()
{
	int col = 0;
	int row = 0;
	int value = 0;
	for (int j = 0; j < this->rows; j++)
	{
		uchar* data = a.ptr<uchar>(j);
		for (int i = 0; i/3 < this->cols;)
		{
			// process each pixel ---------------------     
			if (data[i] != 255 && data[i+1] != 255 && data[i+2] != 255)
			{
				result_list[j * 640 + i/3] = 0;
			}
			else
			{
				result_list[j * 640 + i / 3] = 1;
			}
			i = i + 3;
			//result_list[j * 640 + i] = data[i];
			/*result[j * 640 + i] = data[i];*/
			//value = data[i];
			// end of pixel processing ----------------
		} // end of line    
	}
	return result_list;
}

void Tgraphchecker::deal_point(int* list)
{
	int count = 0;
	while (list[count] != -1)
	{
		int x = list[count] / 640;
		int y = list[count] % 640;
		//Vec3b pixel;
		//pixel[0] = 100;
		//pixel[1] = 100;
		//pixel[2] = 100;
		a.at<Vec3b>(x, y)[0] = 200;
		a.at<Vec3b>(x, y)[1] = 150;
		a.at<Vec3b>(x, y)[2] = 100;
		count = count + 1;
	}
	imwrite("output.png", a);
	return;
}

Tgraphchecker::~Tgraphchecker()
{
}