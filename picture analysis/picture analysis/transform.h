#pragma once
// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "graph_maker.h"
#include  "highgui.hpp"
#include  "imgproc.hpp"
#include  <iostream>
#include  <stdio.h>
using  namespace  cv;
using  namespace  std;

class PerspectiveTransform {
private:
	float a11, a12, a13, a21, a22, a23, a31, a32, a33;
	const int width = 640;
	const int height = 480;
	float* pos;
public:
	
	PerspectiveTransform();
	PerspectiveTransform(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
	PerspectiveTransform(float inA11, float inA21, float inA31, float inA12, float inA22, float inA32, float inA13, float inA23, float inA33);

	PerspectiveTransform quadrilateralToQuadrilateral(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3,
		float x0p, float y0p, float x1p, float y1p, float x2p, float y2p, float x3p, float y3p);
	PerspectiveTransform squareToQuadrilateral(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
	PerspectiveTransform quadrilateralToSquare(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
	PerspectiveTransform buildAdjoint();
	PerspectiveTransform times(PerspectiveTransform other);
	void transformPoints();
	void transformPoints(float *points);
	vector<int> PerspectivePos(int x, int y);
	vector<int> RePerspectivePos(int i, int j);
	PerspectiveTransform &operator=(const PerspectiveTransform &p);
};

class controller {
private:
	float x0, y0, x1, y1, x2, y2, x3, y3;
	float *a;
	const int width = 640;
	const int height = 480;
public:
	controller(float lefttopx, float lefttopy, float righttopx, float righttopy, float rightbotx, float rightboty, float leftbotx, float leftboty);
	~controller();
	void generateArray();
	vector<int> tranformPos(int i, int j);
};

class combineClass {
private:
	controller * imgcontroller;
public:
	combineClass(float lefttopx, float lefttopy, float righttopx, float righttopy, float rightbotx, float rightboty, float leftbotx, float leftboty);
	~combineClass();
	vector<vector<int>> transformMids(Mat m);
};