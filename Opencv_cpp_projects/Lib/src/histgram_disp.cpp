/******************************** 头文件 *************************************/
#include "includes.hpp"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/


/******************************* 私有函数 ************************************/


/**
 * @brief  绘制直方图
 * @param  无
 * @retval 无
 */
int histgram_disp(void)
{
	float histgram[256] = { 0 };
	Mat srcImg = imread("lena.jpg", 0);
	Mat dispHistgram = Mat::zeros(300, 300, CV_8UC3);

	int width = srcImg.cols;
	int height = srcImg.rows;
	float maxHeight = 0;

	/* 统计灰度值概率 */
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			uint8_t index = srcImg.at<uchar>(j, i);
			histgram[index] += 1.0 / (width * height);
			maxHeight = histgram[index] > maxHeight ? histgram[index] : maxHeight;
		}
	}

	/* 显示直方图 */
	for (int i = 0; i < 256; i++) {
		line(dispHistgram, Point(i, 300), Point(i, 300 - (int)(histgram[i] / maxHeight * 300)), CV_RGB(255, 0, 0), 1, 8, 0);
	}

	imshow("srcImg", srcImg);
	imshow("dispHistgram", dispHistgram);

	/* 等待用户按键 */
	waitKey(0);

	destroyAllWindows();

	return 0;
}

/*********************************END OF FILE*********************************/
