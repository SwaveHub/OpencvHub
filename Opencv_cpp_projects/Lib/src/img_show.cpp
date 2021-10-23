/******************************** 头文件 *************************************/
#include "includes.h"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/


/******************************* 私有函数 ************************************/


/**
 * @brief  show一张手动修改像素的灰度图
 * @param  无
 * @retval 无
 */
int img_show(void)
{
	Mat srcImg = imread("lena.jpg");

	int width = srcImg.cols;
	int high = srcImg.rows;

	for (int j = 0; j < high; j++) {
		for (int i = 0; i < width; i++) {
			uint8_t avg = (srcImg.at<Vec3b>(j, i)[0] + srcImg.at<Vec3b>(j, i)[1] + srcImg.at<Vec3b>(j, i)[2]) / 3;
			srcImg.at<Vec3b>(j, i)[0] = avg;
			srcImg.at<Vec3b>(j, i)[1] = avg;
			srcImg.at<Vec3b>(j, i)[2] = avg;
		}
	}
	imshow("transImg", srcImg);

	/* 等待用户按键 */
	waitKey(0);

	return 0;
}

 /*********************************END OF FILE*********************************/
