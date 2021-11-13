/******************************** 头文件 *************************************/
#include "includes.hpp"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/
static string window_name = "binaryImg";

/******************************* 私有函数 ************************************/


/**
 * @brief  回调函数
 * @param  int th, void* data
 * @retval 无
 */
void threshold_Img(int th, void* data)
{
	Mat src = *(Mat*)(data);
	Mat dst;

	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
}

/**
 * @brief  cv回调函数
 * @param  无
 * @retval 状态码
 */
int cv_callback(void)
{
	Mat src_img, gry_img;
	int th_val = 30;
	int th_max = 255;

	src_img = imread("lena.jpg");
	if (!src_img.dataend) {
		cout << "Img loading failed" << endl;
		return -1;
	}

	cvtColor(src_img, gry_img, CV_BGR2GRAY);
	imshow(window_name, gry_img);
	createTrackbar("threshold",
		window_name,
		&th_val,
		th_max,
		threshold_Img,
		&gry_img);

	/* 等待用户按键 */
	waitKey(0);

	return 0;
}

/*********************************END OF FILE*********************************/
