/******************************** 头文件 *************************************/
#include "includes.h"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/


/******************************* 私有函数 ************************************/


/**
 * @brief  肤色检测
 * @param  无
 * @retval 无
 */
int skin_detect(void)
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
		Mat frame_detect;

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

		frame_res.copyTo(frame_detect);

		inRange(frame_hsv, Scalar(i_min_h, i_min_s, i_min_v), Scalar(i_max_h, i_max_s, i_max_v), frame_detect);

		imshow("frame_detect", frame_detect);
		imshow("frame_res", frame_res);
		/* 等待用户按键 */
		waitKey(30);
	}

	destroyAllWindows();

	return 0;
}

 /*********************************END OF FILE*********************************/
