/******************************** 头文件 *************************************/
#include "includes.hpp"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/


/******************************* 私有函数 ************************************/


/**
 * @brief  磨皮
 * @param  无
 * @retval 状态码
 */
int skin_ps(void)
{
	double scale = 0.5;

	/* 0-180 */
	/* 肤色 */
	double i_min_h = 0;
	double i_max_h = 20;

	/* 0-255 */
	double i_min_s = 43;
	double i_max_s = 255;

	/* 0-255 */
	double i_min_v = 55;
	double i_max_v = 255;

	cv::VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "open video failed" << endl;
		return -1;
	}

	for (;;) {
		Mat frame;
		Mat frame_hsv;
		Mat frame_mask;
		Mat frame_detect;
		Mat frame_guss;

		cap >> frame;
		if (!frame.empty()) {

		}
		else {
			cout << "read frame failed" << endl;
		}

		Size img_res = Size(frame.cols * scale, frame.rows * scale);
		Mat frame_res = Mat(img_res, frame.type());

		resize(frame, frame_res, img_res, INTER_LINEAR);
		cvtColor(frame_res, frame_hsv, COLOR_BGR2HSV);

		frame_res.copyTo(frame_mask);

		inRange(frame_hsv, Scalar(i_min_h, i_min_s, i_min_v), Scalar(i_max_h, i_max_s, i_max_v), frame_mask);

		frame_res.copyTo(frame_detect);

		GaussianBlur(frame_res, frame_guss, Size(3, 3), 1, 0);
		frame_guss.copyTo(frame_detect, frame_mask);	/* 从原图中取出目标图像（与运算） */

		imshow("frame_res", frame_res);
		imshow("frame_mask", frame_mask);
		imshow("frame_guss", frame_guss);
		imshow("frame_detect", frame_detect);
		
		/* 等待用户按键 */
		waitKey(30);
	}

	destroyAllWindows();

	return 0;
}

/**
 * @brief  sobel边缘提取
 * @param  无
 * @retval 状态码
 */
int cv_sobel(void)
{
	double scale = 0.5;
	int deepth = CV_8UC1;

	cv::VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "open video failed" << endl;
		return -1;
	}

	for (;;) {
		Mat frame;
		Mat frame_hsv, frame_gray;
		Mat frame_sobel;

		cap >> frame;
		if (!frame.empty()) {

		}
		else {
			cout << "read frame failed" << endl;
		}

		Size frame_size = Size(frame.cols * scale, frame.rows * scale);
		Mat frame_res = Mat(frame_size, frame.type());
		resize(frame, frame_res, frame_size, INTER_LINEAR);

		cvtColor(frame_res, frame_gray, CV_BGR2GRAY);

		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;

		Sobel(frame_res, grad_x, deepth, 1, 0, 3);
		convertScaleAbs(grad_x, abs_grad_x);

		Sobel(frame_res, grad_y, deepth, 0, 1, 3);
		convertScaleAbs(grad_y, abs_grad_y);

		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, frame_sobel);

		imshow("frame_sobel", frame_sobel);
		imshow("frame_res", frame_res);

		/* 等待用户按键 */
		waitKey(30);
	}

	destroyAllWindows();

	return 0;
}

/**
 * @brief  滤波
 * @param  无
 * @retval 状态码
 */
int cv_blur(void)
{
	double scale = 0.5;

	cv::VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "open video failed" << endl;
		return -1;
	}

	for (;;) {
		Mat frame, frame_midian_blur, frame_blur, frame_gaussian_blur;

		cap >> frame;
		if (!frame.empty()) {

		}
		else {
			cout << "read frame failed" << endl;
		}

		Size frame_size = Size(frame.cols * scale, frame.rows * scale);
		Mat frame_res = Mat(frame_size, frame.type());
		resize(frame, frame_res, frame_size, INTER_LINEAR);

		medianBlur(frame_res, frame_midian_blur, 5);
		blur(frame_res, frame_blur, Size(5, 5));
		GaussianBlur(frame_res, frame_gaussian_blur, Size(5, 5), 0, 0);

		imshow("frame_midian_blur", frame_midian_blur);
		imshow("frame_blur", frame_blur);
		imshow("frame_gaussian_blur", frame_gaussian_blur);
		imshow("frame_res", frame_res);
		/* 等待用户按键 */
		waitKey(30);
	}

	destroyAllWindows();

	return 0;
}

/*********************************END OF FILE*********************************/
