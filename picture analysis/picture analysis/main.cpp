//#define CRTDBG_MAP_ALLOC  

//#include <stdlib.h>
//#include <crtdbg.h>
#include "cv.h"
#include "opencv.hpp"
#include "highgui.h"
#include <iostream>
#include "transform.h"
#include "graph_checker.h"
#include "graph_maker.h"
#include "graph_capture.h"



using namespace std;
using namespace cv;


//int main()
//{
//	//int* pointer = new int[2];
//	//VideoCapture capture;
//	//capture.open(0);
//	//capture.set(CAP_PROP_FRAME_WIDTH, 640.0);
//	//capture.set(CAP_PROP_FRAME_HEIGHT, 360.0);
//	//while (1)
//	//{
//	//	Mat frame;
//	//	capture >> frame;
//	//	cout<<frame.cols;
//	//	cout<<frame.rows;
//	//	cout << endl;
//	//	//image i = image();
//	//	//i.read(frame);
//	//	imshow("读取视频", frame);
//	//	//i.printMid(frame);
//	//	//imshow("test", frame);
//	//	//waitKey(40);
//	//}
//	//EnableMemLeakCheck();
//	VideoCapture cap;
//	cap.open(0);
//	//cap.set(CAP_PROP_FRAME_WIDTH, 640.0);
//	//cap.set(CAP_PROP_FRAME_HEIGHT, 360.0);
//	Mat frame;
//	char a;
//	for (;;)
//	{
//		cap >> frame;
//		if (frame.empty())
//			break;
//		image i = image();
//		i.read(frame);
//		i.printMid(frame);
//		imshow("test", frame);
//		//imshow("FG Segmentation", frame);
//
//
//		int c = waitKey(30);
//		if (c == 'q' || c == 'Q' || (c & 255) == 27)
//			break;
//	}
//	
//	return 0;
//
//}

//int main()
//{
//	//int hello = 0;
//	//hello++;
//	//int* pointer = new int[2];
//	//Tgraphchecker _graph = Tgraphchecker("test12.png");
//	//int you = 0;
//	//auto result = _graph.result();
//	//image *fuck = new image(result);
//	//fuck->read();
//	//_graph.deal_point(fuck->findMid(pointer));
//	//char ch;
//	//cin >> ch;
//	int* pointer = new int[2];
//	VideoCapture capture;//若测试摄像头有没有打开，/*if(!capture.isOpened())
//	capture.open(0);
//
//	while (1)
//	{
//		Mat frame; //定义一个Mat变量，用于存储每一帧的图像
//		capture >> frame;  //读取当前帧
//		auto _graph = Tgraphcapturer(frame);
//		auto result = _graph.result();
//		if (frame.empty())
//		{
//			printf("--(!) No captured frame -- Break!");
//			break;
//		}
//		else
//		{
//			image *fuck = new image(result);
//			fuck->read();
//			imshow("test", _graph.deal_point(fuck->findMid(pointer))); //显示当前帧
//		}
//
//		waitKey(50); //延时50ms
//	}
//	return 0;
//}

//int main() {
//	Mat img = imread("test13.png");
//	int img_height = img.rows;
//
//	int img_width = img.cols;
//
//	Mat img_trans = Mat::zeros(img_height, img_width, CV_8UC3);
//	image i = image();
//	i.read(img);
//	vector<vector<int>> result = i.findMid();
//	//i.print();
//	PerspectiveTransform t = PerspectiveTransform(70, 77, 505, 58, 61, 325, 488, 398);
//	PerspectiveTransform tansform = t.quadrilateralToQuadrilateral(0,0,639,0,0,479,639,479, 70, 77, 505, 58, 61, 325, 488, 398);
//	tansform.transformPoints();
//	//i.printMid(img);
//	//imwrite("result3.png",img);
//	controller c = controller(70, 77, 505, 58, 488, 398, 61, 325);
//	c.generateArray();
//	//for (vector<int> &v : result) {
//	//	//vector<int> out=c.tranformPos(v[0], v[1]);
//	//	//cout << out[0] << ',' << out[1] << endl;
//	//	/*if (!(tansform.RePerspectivePos(v[0], v[1])[0] == -1))
//	//	{
//	//		cout << v[0] << ',' << v[1] << " ";
//	//		cout << tansform.RePerspectivePos(v[0], v[1])[0] << ',' << tansform.RePerspectivePos(v[0], v[1])[1] << endl;
//	//	}*/
//	//}
//	for (int i = 0;i<img_height;i++) {
//		uchar*  t = img_trans.ptr<uchar>(i);
//		for (int j = 0;j<img_width;j++) {
//			/*int tmp = i * img_width + j;
//			int x = tansform.pos[tmp * 2];
//			int y = tansform.pos[tmp * 2 + 1];*/
//			int x = tansform.PerspectivePos(i, j)[0];
//			int y = tansform.PerspectivePos(i, j)[1];
//			if (x<0 || x>(img_width - 1) || y<0 || y>(img_height - 1))
//				continue;
//			uchar* p = img.ptr<uchar>(y);
//			t[j * 3] = p[x * 3];
//			t[j * 3 + 1] = p[x * 3 + 1];
//			t[j * 3 + 2] = p[x * 3 + 2];
//		}
//	}
//	for (vector<int> &v : result) {
//		cout << v[1] << ',' << v[0] << " ";
//		if (!(tansform.RePerspectivePos(v[1], v[0])[0] == -1))
//		{
//		cout << v[1] << ',' << v[0] << " ";
//		cout << tansform.RePerspectivePos(v[1], v[0])[0] << ',' << tansform.RePerspectivePos(v[1], v[0])[1] << endl;
//		}
//		if (!(c.tranformPos(v[1], v[0])[0] == -1)) {
//			cout<<"c" << v[1] << ',' << v[0] << " ";
//			cout << c.tranformPos(v[1], v[0])[0] << ',' << c.tranformPos(v[1], v[0])[1] << endl;
//		}
//		circle(img_trans, Point(tansform.RePerspectivePos(v[1], v[0])[1] + 1, tansform.RePerspectivePos(v[1], v[0])[0] + 1), 2, cvScalar(255, 0, 0), -1);
//		cout << "end" << endl;
//	}
//	
//	imwrite("trans1.png", img_trans);
//	char q;
//	cin >> q;
//}

//int main() {
//	//string inputname;
//	//getline(cin,inputname);
//	Mat img = imread("test14.png");
//	int img_height = img.rows;
//
//	int img_width = img.cols;
//
//	Mat img_trans = Mat::zeros(img_height, img_width, CV_8UC3);
//	PerspectiveTransform t = PerspectiveTransform(33, 96, 459, 137, 38, 408,459, 348);
//	PerspectiveTransform tansform = t.quadrilateralToQuadrilateral(0, 0, 639, 0, 0, 479, 639, 479, 33, 96, 459, 137, 38, 408, 459, 348);
//	tansform.transformPoints();
//	controller c = controller(33, 96, 459, 137, 459, 348, 38, 408);
//	c.generateArray();
//	combineClass cc = combineClass(70, 77, 505, 58, 488, 398, 61, 325);
//	image i = image();
//	i.read(img);
//	vector<vector<int>> result = i.findMid();
//	//for (vector<int> &v : result) {
//	//	//vector<int> out=c.tranformPos(v[0], v[1]);
//	//	//cout << out[0] << ',' << out[1] << endl;
//	//	/*if (!(tansform.RePerspectivePos(v[0], v[1])[0] == -1))
//	//	{
//	//		cout << v[0] << ',' << v[1] << " ";
//	//		cout << tansform.RePerspectivePos(v[0], v[1])[0] << ',' << tansform.RePerspectivePos(v[0], v[1])[1] << endl;
//	//	}*/
//	//}
//	for (int i = 0;i<img_height;i++) {
//		uchar*  t = img_trans.ptr<uchar>(i);
//		for (int j = 0;j<img_width;j++) {
//			/*int tmp = i * img_width + j;
//			int x = tansform.pos[tmp * 2];
//			int y = tansform.pos[tmp * 2 + 1];*/
//			int x = tansform.PerspectivePos(i, j)[0];
//			int y = tansform.PerspectivePos(i, j)[1];
//			if (x<0 || x>(img_width - 1) || y<0 || y>(img_height - 1))
//				continue;
//			uchar* p = img.ptr<uchar>(y);
//			t[j * 3] = p[x * 3];
//			t[j * 3 + 1] = p[x * 3 + 1];
//			t[j * 3 + 2] = p[x * 3 + 2];
//		}
//	}
//	for (vector<int> &v : result) {
//		//cout << v[1] << ',' << v[0] << " ";
//		if (!(tansform.RePerspectivePos(v[1], v[0])[0] == -1))
//		{
//			cout << v[1] << ',' << v[0] << " ";
//			cout << tansform.RePerspectivePos(v[1], v[0])[0] << ',' << tansform.RePerspectivePos(v[1], v[0])[1] << endl;
//			circle(img_trans, Point(tansform.RePerspectivePos(v[1], v[0])[1] + 1, tansform.RePerspectivePos(v[1], v[0])[0] + 1), 2, cvScalar(255, 0, 0), -1);
//		}
//		/*if (!(c.tranformPos(v[1], v[0])[0] == -1)) {
//			cout << "c" << v[1] << ',' << v[0] << " ";
//			cout << c.tranformPos(v[1], v[0])[0] << ',' << c.tranformPos(v[1], v[0])[1] << endl;
//		}
//		cout << "end" << endl;*/
//		//cout << v[0] << ',' << v[1] << endl;
//		//circle(img_trans, Point(v[1] + 1, v[0] + 1), 2, cvScalar(255, 0, 0), -1);
//	}
//
//	imwrite("trans3.png", img_trans);
//	char q;
//	cin >> q;
//}

int main() {
	Mat img = imread("test16.png");
	image i = image();
	i.read(img);
	i.printMid(img);

	combineClass cc = combineClass(127,75,494,69,456,416,82,351);
	Mat o = imread("test9.png");
	vector<vector<int>> result = cc.transformMids(img);
	for (vector<int> &v : result) {
		cout << v[0] << ',' << v[1] << endl;
		circle(o,Point(v[0]+1,v[1]+1),2, cvScalar(255, 0, 0), -1);
	}
	imwrite("output5.png", o);
	char q;
	cin >> q;
}

//int main() {
//	PerspectiveTransform t= PerspectiveTransform(33, 96, 459, 137, 38, 408, 459, 348);
//	PerspectiveTransform tansform = t.quadrilateralToQuadrilateral(0, 0, 639, 0, 0, 479, 639, 479, 33, 96, 459, 137, 38, 408, 459, 348);
//	tansform.transformPoints();
//	cout<<tansform.RePerspectivePos(164,189)[0]<<" "<< tansform.RePerspectivePos(164, 189)[1];
//	char q;
//	cin >> q;
//}