#include "pch.h"
#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;
String str = "Sample Text";																	//ȭ�鿡 ������ �ؽ�Ʈ
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
		Mat imageROI(frame, Rect(mx, my, logo.cols, logo.rows));							// ������ ���ɿ��� (ROI) ���� 
		if (mx + 259 > frame.cols - 10 || mx < 10) { //frame.cols -10  /760					// ������ �����ڸ��� ����� �ϴ� ���ǹ�
			x = x * (-1);
		}
		if (my + 194 > frame.rows - 10 || my < 10) { //frame.rows -10  /560
			y = y * (-1);
		}
		mx = mx + x;
		my = my + y;
		if (lx < 760) {																		// ���󿡼� �����ִٰ� ���󿡼� ������� �ٽ� ���̰� �ϴ� �ڵ�
			lx += 1;
		}
		else {
			lx = -10;
		}
		Mat mask(230 - logo_gray);															// ����ũ
		putText(frame, str, Point(lx, 560), FONT_HERSHEY_COMPLEX, 2, Scalar(25, 255, 25));
		logo.copyTo(imageROI, mask);														// ����ũ ���� 0�� �ƴ� ��ġ���� �ΰ� ROI�� ����(�ΰ��� �� ����� ���ֱ� ���� ���)
		imshow("Image", frame);																// �̹��� ���Ե� ���� ������
		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27) break;
	}


	return 0;
}