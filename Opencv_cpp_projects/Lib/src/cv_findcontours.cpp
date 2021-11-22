/******************************** 头文件 *************************************/
#include "includes.hpp"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/


/******************************* 私有函数 ************************************/


/**
 * @brief  轮廓检测
 * @param  无
 * @retval 无
 */
int cv_findhole(void)
{
	Mat img_src = imread("hole.png");
	Mat img_gray;
	Mat img_binary;

	cvtColor(img_src, img_gray, COLOR_BGR2GRAY);

	/* 反色 */
	img_gray = 255 - img_gray;

	/* 二值化 */
	threshold(img_gray, img_binary, 150, 255, THRESH_BINARY);	
	morphologyEx(img_binary, img_binary, MORPH_OPEN, 5, Point(-1, -1), 2);

	/* 高斯模糊 */
	GaussianBlur(img_binary, img_binary, Size(3, 3), 0, 0);

	/* 轮廓检测 */
	vector<vector<Point>> contours;
	findContours(img_binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		float ratio = 0;
		if (rbox.size.width) {
			ratio = rbox.size.height / rbox.size.width;
		}

		if (abs(ratio - 1) < 0.1 && rbox.size.area() > 1000) {
			drawContours(img_src, contours, i, Scalar(0, 255, 255), -1, 8);
		}
	}

	imshow("img_src", img_src);
	imshow("img_binary", img_binary);
	/* 等待用户按键 */
	waitKey(0);

	return 0;
}

/**
 * @brief  轮廓检测
 * @param  无
 * @retval 无
 */
int cv_findchip(void)
{
	Mat img_src = imread("chip.png");
	Mat img_gray;
	Mat img_binary;

	cvtColor(img_src, img_gray, COLOR_BGR2GRAY);

	/* 高斯去噪 */
	GaussianBlur(img_gray, img_gray, Size(3, 3), 0, 0);

	/* 二值化 */
	threshold(img_gray, img_binary, 160, 255, THRESH_BINARY);	
	morphologyEx(img_binary, img_binary, MORPH_CLOSE, 3);

	/* 轮廓检测 */
	vector<vector<Point>> contours;
	findContours(img_binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		float ratio = 0;
		if (rbox.size.width) {
			ratio = rbox.size.height / rbox.size.width;
		}
		
		if (rbox.size.area() > 1000 && abs(ratio - 1) < 0.1) {
			drawContours(img_src, contours, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; i++) {
				line(img_src, vtx[i], vtx[i < 3 ? i + 1 : 0], Scalar(0, 0, 255), 4);
			}
			cout << "ratio:" << ratio << endl;
			cout << rbox.size.area() << "," << rbox.size.height << "," << rbox.size.width << endl;
		}
	}

	imshow("img_src", img_src);
	imshow("img_binary", img_binary);
	/* 等待用户按键 */
	waitKey(0);

	return 0;
}

/**
 * @brief  轮廓检测
 * @param  无
 * @retval 无
 */
int cv_findcup(void)
{
	/* 0-180 */
	double i_min_h1 = 0;
	double i_max_h1 = 5;
	double i_min_h2 = 170;
	double i_max_h2 = 180;

	/* 0-255 */
	double i_min_s = 50;
	double i_max_s = 255;

	/* 0-255 */
	double i_min_v = 80;
	double i_max_v = 255;

	Mat img_src = imread("cup.png");
	Mat img_hsv;
	Mat img_gray;
	Mat img_binary;
	Mat img_mask1, img_mask2;

	/* 颜色筛选 */
	cvtColor(img_src, img_hsv, COLOR_BGR2HSV);
	inRange(img_hsv, Scalar(i_min_h1, i_min_s, i_min_v), Scalar(i_max_h1, i_max_s, i_max_v), img_mask1);
	inRange(img_hsv, Scalar(i_min_h2, i_min_s, i_min_v), Scalar(i_max_h2, i_max_s, i_max_v), img_mask2);
	img_binary = img_mask1 | img_mask2;

	/* 高斯模糊 */
	GaussianBlur(img_binary, img_binary, Size(3, 3), 0, 0);

	/* 轮廓检测 */
	vector<vector<Point>> contours;
	findContours(img_binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		if (rbox.size.area() > 2000) {
			Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; i++) {
				line(img_src, vtx[i], vtx[i < 3 ? i + 1 : 0], Scalar(0, 255, 0), 2);
			}
			cout << rbox.size.area() << "," << rbox.size.height << "," << rbox.size.width << endl;
		}
	}

	imshow("img_src", img_src);
	imshow("img_binary", img_binary);

	/* 等待用户按键 */
	waitKey(0);

	return 0;
}

 /*********************************END OF FILE*********************************/
