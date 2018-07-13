#include "transform.h"
#include  "highgui.hpp"
#include  "imgproc.hpp"
#include  <iostream>
#include  <stdio.h>
using  namespace  cv;
using  namespace  std;

PerspectiveTransform::PerspectiveTransform() {}
PerspectiveTransform::PerspectiveTransform(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	a13 = 0; a23 = 0; a33 = 1;
	float dx31 = x3 - x1; float dx32 = x3 - x2;
	float dy31 = y3 - y1; float dy32 = y3 - y3;
	float det = dx31 * dy32 - dx32 * dy31;
	a31 = (x1*dy32 - y1 * dx32) / det;
	a32 = (y2*dx31 - x2 * dy31) / det;
	a11 = x1 * (1 + a31);
	a12 = x2 * (1 + a32);
	a21 = y1 * (1 + a31);
	a22 = y2 * (1 + a32);
}

PerspectiveTransform::PerspectiveTransform(float inA11, float inA21, float inA31, float inA12, float inA22, float inA32, float inA13, float inA23, float inA33) :
	a11(inA11), a12(inA12), a13(inA13), a21(inA21), a22(inA22), a23(inA23), a31(inA31), a32(inA32), a33(inA33) {}

PerspectiveTransform PerspectiveTransform::quadrilateralToQuadrilateral(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, float x0p, float y0p, float x1p, float y1p, float x2p, float y2p, float x3p, float y3p) {
	PerspectiveTransform qToS = PerspectiveTransform::quadrilateralToSquare(x0, y0, x1, y1, x2, y2, x3, y3);
	PerspectiveTransform sToQ = PerspectiveTransform::squareToQuadrilateral(x0p, y0p, x1p, y1p, x2p, y2p, x3p, y3p);
	return sToQ.times(qToS);
}

PerspectiveTransform PerspectiveTransform::squareToQuadrilateral(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	float dx3 = x0 - x1 + x2 - x3;
	float dy3 = y0 - y1 + y2 - y3;
	if (dx3 == 0.0f && dy3 == 0.0f) {
		PerspectiveTransform result(PerspectiveTransform(x1 - x0, x2 - x1, x0, y1 - y0, y2 - y1, y0, 0.0f, 0.0f, 1.0f));
		return result;
	}
	else {
		float dx1 = x1 - x2;
		float dx2 = x3 - x2;
		float dy1 = y1 - y2;
		float dy2 = y3 - y2;
		float denominator = dx1 * dy2 - dx2 * dy1;
		float a13 = (dx3 * dy2 - dx2 * dy3) / denominator;
		float a23 = (dx1 * dy3 - dx3 * dy1) / denominator;
		PerspectiveTransform result(PerspectiveTransform(x1 - x0 + a13 * x1, x3 - x0 + a23 * x3, x0, y1 - y0 + a13 * y1, y3 - y0 + a23 * y3, y0, a13, a23, 1.0f));
		return result;
	}
}

PerspectiveTransform PerspectiveTransform::quadrilateralToSquare(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	// Here, the adjoint serves as the inverse:
	return squareToQuadrilateral(x0, y0, x1, y1, x2, y2, x3, y3).buildAdjoint();
}

PerspectiveTransform PerspectiveTransform::buildAdjoint() {
	// Adjoint is the transpose of the cofactor matrix:
	PerspectiveTransform result(PerspectiveTransform(a22 * a33 - a23 * a32,
		a23 * a31 - a21 * a33, a21 * a32 - a22 * a31, a13 * a32 - a12 * a33, a11 * a33 - a13 * a31,
		a12 * a31 - a11 * a32, a12 * a23 - a13 * a22, a13 * a21 - a11 * a23, a11 * a22 - a12 * a21));
	return result;
}

PerspectiveTransform PerspectiveTransform::times(PerspectiveTransform other) {
	PerspectiveTransform result(PerspectiveTransform(a11 * other.a11 + a21 * other.a12 + a31 * other.a13,
		a11 * other.a21 + a21 * other.a22 + a31 * other.a23, a11 * other.a31 + a21 * other.a32 + a31
		* other.a33, a12 * other.a11 + a22 * other.a12 + a32 * other.a13, a12 * other.a21 + a22
		* other.a22 + a32 * other.a23, a12 * other.a31 + a22 * other.a32 + a32 * other.a33, a13
		* other.a11 + a23 * other.a12 + a33 * other.a13, a13 * other.a21 + a23 * other.a22 + a33
		* other.a23, a13 * other.a31 + a23 * other.a32 + a33 * other.a33));
	return result;
}

void PerspectiveTransform::transformPoints() {
	float *points = new float[height*width * 2];
	int count = 0;
	for (int i = 0;i<height;i++) {
		for (int j = 0;j<width;j++) {
			points[count] = j;
			points[count + 1] = i;
			count += 2;
		}
	}

	int max = height * width * 2;
	for (int i = 0; i < max; i += 2) {
		float x = points[i];
		float y = points[i + 1];
		float denominator = a13 * x + a23 * y + a33;
		points[i] = (a11 * x + a21 * y + a31) / denominator;
		points[i + 1] = (a12 * x + a22 * y + a32) / denominator;
		//cout << (int)points[i] << ',' << (int)points[i + 1] << " ";
	}
	pos = points;
}

void PerspectiveTransform::transformPoints(float *points) {
	int max = height * width * 2;
	for (int i = 0; i < max; i += 2) {
		float x = points[i];
		float y = points[i + 1];
		float denominator = a13 * x + a23 * y + a33;
		points[i] = (a11 * x + a21 * y + a31) / denominator;
		points[i + 1] = (a12 * x + a22 * y + a32) / denominator;
		//cout << (int)points[i] << ',' << (int)points[i + 1] << " ";
	}
}

vector<int> PerspectiveTransform::PerspectivePos(int x, int y) {
	int temp = x * width + y;
	int r = pos[temp * 2];
	int c = pos[temp * 2 + 1];
	return vector<int> {r, c};
}

vector<int> PerspectiveTransform::RePerspectivePos(int i, int j) {
	int max = height * width;
	for (int c = 0;c < max;c++) {
		if ((int)pos[c * 2] == i && (int)pos[c * 2 + 1] == j) return vector<int>{c / width, c%width};
	}
	return vector<int>{-1, -1};
}

PerspectiveTransform &PerspectiveTransform::operator=(const PerspectiveTransform &p) {
	a11 = p.a11; a12 = p.a12; a13 = p.a13;
	a21 = p.a21; a22 = p.a22; a23 = p.a23;
	a31 = p.a31; a32 = p.a32; a33 = p.a33;
	return *this;
}

//controller////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
controller::controller(float lefttopx, float lefttopy, float righttopx, float righttopy, float rightbotx, float rightboty, float leftbotx, float leftboty) :
	x0(lefttopx), y0(lefttopy), x1(righttopx), y1(righttopy), x2(leftbotx), y2(leftboty), x3(rightbotx), y3(rightboty)
{
	a = new float[height*width * 2];
	int count = 0;
	for (int i = 0;i<height;i++) {
		for (int j = 0;j<width;j++) {
			a[count] = j;
			a[count + 1] = i;
			count += 2;
		}
	}
}
controller::~controller() { delete a; }

void controller::generateArray() {
	PerspectiveTransform t = PerspectiveTransform(x0, y0, x1, y1, x2, y2, x3, y3);
	PerspectiveTransform transform = t.quadrilateralToQuadrilateral(
		0, 0, 639, 0, 0, 479, 639, 479,
		x0, y0, x1, y1, x2, y2, x3, y3);
	transform.transformPoints(a);
}

vector<int> controller::tranformPos(int i, int j) {
	int max = height * width;
	for (int c = 0;c < max;c++) {
		if ((int)a[c * 2] == i && (int)a[c * 2 + 1] == j) return vector<int>{c / width, c%width};
	}
	return vector<int>{-1, -1};
}

//combineClass//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
combineClass::combineClass(float lefttopx, float lefttopy, float righttopx, float righttopy, float rightbotx, float rightboty, float leftbotx, float leftboty) {
	imgcontroller = new controller(lefttopx, lefttopy, righttopx, righttopy, rightbotx, rightboty, leftbotx, leftboty);
	imgcontroller->generateArray();
}

combineClass::~combineClass() { delete imgcontroller; }

vector<vector<int>> combineClass::transformMids(Mat m) {
	image i = image();
	i.read(m);
	vector<vector<int>> mids = i.findMid();
	vector<vector<int>> result;
	for (vector<int> &v : mids) {
		vector<int> r = imgcontroller->tranformPos(v[1], v[0]);
		if (r[0] != -1) result.push_back(vector<int> {r[1], r[0]});
	}
	return result;
}