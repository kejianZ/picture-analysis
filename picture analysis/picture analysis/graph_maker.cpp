#include"graph_maker.h"
#include <vector>
#include <iostream>
#include "cv.h"
#include "opencv.hpp"
#include "highgui.h"
using namespace cv;
using namespace std;

segment::segment(int row, int begin) { row_num = row; startPoint = begin; }
segment::~segment() {}

int segment::get_shape() { return shape_num; }
void segment::set_shape(int s) { shape_num = s; }

int segment::get_rowNum() { return row_num; }
int segment::get_length() { return length; }

void segment::set_len(int l) { length = l; }

bool segment::adjacent(segment *s) {
	int s_start = s->startPoint; int s_end = s->startPoint + s->length - 1;
	int start = startPoint; int end = startPoint + length - 1;
	return ((start <= s_end) && (end >= s_start)) ? true : false;
}

vector<vector<int>> segment::print() {
	vector<vector<int>> result;
	for (int c = 0; c < length; c++) {
		vector<int> point;
		point.push_back(row_num); point.push_back(startPoint + c);
		result.push_back(point);
	}
	return result;
}
int segment::midPoint() { return startPoint + length / 2; }

//shape/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
shape::shape(int x) { index = x; }
shape::~shape(){for (segment* &i : segments) delete i;}

vector<segment *> shape::getSegments() {return segments;}

void shape::add(segment *s) { segments.push_back(s); }

void shape::clear() {
	vector<segment *> n;
	segments = n;
}

void shape::comb(shape *s) {
	int size = segments.size(); int s_size = s->segments.size();
	segments.resize(size + s_size);
	for (int c = size; c < size + s_size; c++) {
		segments[c] = s->segments[c - size];
	}
	//segments.insert(segments.begin() + size, s->segments.begin(), s->segments.end());
	s->clear();
}

bool shape::empty() {
	return segments.size() == 0 ? true : false;
}

vector<vector<int>> shape::print() {
	vector<vector<int>> result;
	for (segment* &s : segments) {
		vector<vector<int>> l = s->print();
		result.insert(result.end(), l.begin(), l.end());
	}
	return result;
}

int shape::size() {
	return segments.size();
}

bool shape::tooSmall() {
	if (segments.size() < 5) return true;
	int rows = 0; int tpoints = 0;
	for (segment* &s : segments) {
		tpoints += s->get_length();
		rows++;
	}
	if (tpoints / rows < 4) return true;
	return false;
}

void shape::printMid(Mat m) {
	//if (segments.size() < 5) return;
	//if (tooSmall()) return;
	int x = 0;	int y = 0;
	for (segment* &s : segments) {
		x += s->get_rowNum();
		y += s->midPoint();
	}
	x /= segments.size();
	y /= segments.size();
	circle(m, Point(y + 1, x + 1), 2, cvScalar(255, 0, 0), -1);
}

vector<int> shape::midPoint() {
	//if (segments.size() < 5) return;
	int x = 0;	int y = 0;
	for (segment* &s : segments) {
		x += s->get_rowNum();
		y += s->midPoint();
	}
	x /= segments.size();
	y /= segments.size();
	return vector<int> {x, y};
}

//image///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
image::image() { }
image::~image()
{
	for (auto &i : shapes)
	{
		if (i) delete i;
	}
}

void image::readrow(int row_num, cv::Mat cavas) {
	vector<segment *> curline;
	uchar* data = cavas.ptr<uchar>(row_num);
	for (int c = 0; c < w; c++) {
		if (data[3 * c] >250 && data[3 * c + 1] >250 && data[3 * c + 2]>250) {
			segment *s = new segment(row_num, c);

			int head = c;
			while (c < w && data[3 * c] >250 && data[3 * c + 1] >250 && data[3 * c + 2]>250) c++;
			s->set_len(c - head);

			vector<int> shape_ind;  //the index of lines in last row which l adjacent to
			for (segment* &ss : lastrow) {
				if (s->adjacent(ss) && (find(shape_ind.begin(), shape_ind.end(), ss->get_shape()) == shape_ind.end())) shape_ind.push_back(ss->get_shape());
			}

			if (shape_ind.size() == 0) {
				s->set_shape(shapes.size());
				shape *sh = new shape(shapes.size());
				sh->add(s);
				shapes.push_back(sh);
			}    //create a new shape
			else if (shape_ind.size() == 1) {
				s->set_shape(shape_ind[0]);
				shapes[shape_ind[0]]->add(s);
			}
			else {
				for (int cc = 1; cc < shape_ind.size(); cc++) {
					shapes[shape_ind[0]]->comb(shapes[shape_ind[cc]]);
				}
				s->set_shape(shape_ind[0]);
				shapes[shape_ind[0]]->add(s);
			}

			curline.push_back(s);
		}
	}
	lastrow = curline;
}

void image::read(cv::Mat cavas) {
	for (int c = 0; c < h; c++) {
		readrow(c, cavas);
	}
	int size = shapes.size();
	vector<shape *> newshapes;
	for (int c = 0;c < size;c++) {
		if ((!shapes[c]->empty()) && (!shapes[c]->tooSmall())) newshapes.push_back(shapes[c]);
		else delete shapes[c];
	}
	shapes = newshapes;
}

void image::print() {
	vector<vector<int>> img;
	for (int c = 0; c < h; c++) {
		vector<int> l(w);
		img.push_back(l);
	}
	for (shape* &s : shapes) {
		vector<vector<int>> t = s->print();
		for (vector<vector<int>>::iterator titr = t.begin(); titr != t.end(); titr++) {
			vector<int> pos = *titr;
			img[pos[0]][pos[1]] = 1;
		}
	}

	int* pixel = new int[2];
	vector<vector<int>> mids = findMid();
	for (int c = 0; c < shapes.size(); c++) {
		img[mids[c][0]][mids[c][1]] = 8;
	}

	for (int c = 0; c < h; c++) {
		for (int cc = 0; cc < w; cc++) {
			cout << img[c][cc];
		}
		cout << endl;
	}
}

void image::printMid(cv::Mat m) {
	int size = shapes.size();
	for (int c = 0; c < size; c++) { if (shapes[c]) shapes[c]->printMid(m); }
}
vector<vector<int>> image::findMid() {
	vector<vector<int>> r;
	int size = shapes.size();
	for (int c = 0; c < size; c++) { if (shapes[c]) r.push_back(shapes[c]->midPoint()); }
	return r;
}