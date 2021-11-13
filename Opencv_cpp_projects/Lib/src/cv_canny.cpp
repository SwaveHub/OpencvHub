/******************************** 头文件 *************************************/
#include "includes.hpp"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/


/******************************* 私有函数 ************************************/


/**
 * @brief  Canny边缘检测
 * @param  无
 * @retval 无
 */
int cv_canny(void)
{
	int deepth = CV_16SC1;

	Mat img_src = imread("lena.jpg");
	Mat img_gray;
	Mat	img_canny;

	cvtColor(img_src, img_gray, COLOR_BGR2GRAY);

	Mat grad_x, grad_y;

	Sobel(img_src, grad_x, deepth, 1, 0, 3);
	Sobel(img_src, grad_y, deepth, 0, 1, 3);

	Canny(grad_x, grad_y, img_canny, 50, 150, false);
	imshow("img_canny_1", img_canny);

	Canny(img_gray, img_canny, 50, 150, 3, false);
	imshow("img_canny2", img_canny);

	/* 等待用户按键 */
	waitKey(0);

	return 0;
}

 /*********************************END OF FILE*********************************/
