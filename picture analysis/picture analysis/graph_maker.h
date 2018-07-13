#pragma once
// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#include <vector>
#include <iostream>
#include "cv.h"
#include "opencv.hpp"
#include "highgui.h"

using namespace std;

#define h 480
#define w 640
//vector<int, int> i;

class segment {
private:
	int row_num;
	int shape_num;   //which shape this line belongs to
	int startPoint;
	int length;
public:
	segment(int row, int begin);
	~segment();

	int get_shape();
	void set_shape(int s);
	int get_rowNum();
	int get_length();
	void set_len(int l);

	bool adjacent(segment *s);
	vector<vector<int>> print();
	int midPoint();
};

class shape {
private:
	int index;
	vector<segment *> segments;
public:
	shape(int x);
	~shape();

	vector<segment *> getSegments();

	void add(segment *s);
	void clear();
	void comb(shape *s);
	bool empty();
	vector<vector<int>> print();
	int size();
	bool tooSmall();
	void printMid(cv::Mat m);
	vector<int> midPoint();
};


class image {
public:
	vector<shape *> shapes;
	vector<segment *> lastrow;
public:
	image();
	~image();

	void readrow(int row_num, cv::Mat cavas);
	void read(cv::Mat cavas);
	void print();
	void printMid(cv::Mat m);
	vector<vector<int>> findMid();
};
