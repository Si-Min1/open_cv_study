#include "pch.h"
#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;
String str = "Sample Text";																	//화면에 보여줄 텍스트
int lx = -10;
int p = 0;
int mx = 20, my = 20;
int x = 1, y = 1;
Mat frame;
int main() {
	Mat logo = cv::imread("C:\\Users\\admin\\Desktop\\20173208\\HappyFish.jpg");
	Mat logo_gray = cv::imread("C:\\Users\\admin\\Desktop\\20173208\\HappyFish.jpg", IMREAD_GRAYSCALE);
	VideoCapture capture("C:\\Users\\admin\\Desktop\\20173208\\vtest.avi", IMREAD_GRAYSCALE);
	if (!capture.isOpened()) {
		//error in opening the video input
		cerr << "Unable to open: " << endl;
		return 0;
	}

	while (true) {
		capture >> frame;
		if (frame.empty()) break;
		Mat imageROI(frame, Rect(mx, my, logo.cols, logo.rows));							// 영상의 관심영역 (ROI) 정의 
		if (mx + 259 > frame.cols - 10 || mx < 10) { //frame.cols -10  /760					// 영상의 가장자리에 틩기게 하는 조건문
			x = x * (-1);
		}
		if (my + 194 > frame.rows - 10 || my < 10) { //frame.rows -10  /560
			y = y * (-1);
		}
		mx = mx + x;
		my = my + y;
		if (lx < 760) {																		// 영상에서 보여주다가 영상에서 사라지면 다시 보이게 하는 코드
			lx += 1;
		}
		else {
			lx = -10;
		}
		Mat mask(230 - logo_gray);															// 마스크
		putText(frame, str, Point(lx, 560), FONT_HERSHEY_COMPLEX, 2, Scalar(25, 255, 25));
		logo.copyTo(imageROI, mask);														// 마스크 값이 0이 아닌 위치에만 로고를 ROI에 삽입(로고의 흰 배경을 없애기 위한 방법)
		imshow("Image", frame);																// 이미지 삽입된 영상 보여줌
		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27) break;
	}


	return 0;
}