/******************************** 头文件 *************************************/
#include "includes.hpp"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/


/******************************* 私有函数 ************************************/


/**
 * @brief  提取像素单通道值
 * @param  无
 * @retval 状态码
 */
int channel_show(void)
{
	cv::Mat srcImg = imread("solar_panel.png");

	std::vector<cv::Mat> channels;
	cv::split(srcImg, channels);

	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);

	imshow("Red", R);
	imshow("Green", G);
	imshow("Blue", B);
	imshow("srcImg", srcImg);

	/* 等待用户按键 */
	waitKey(0);

	destroyAllWindows();

	return 0;
}

/*********************************END OF FILE*********************************/
