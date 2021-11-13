/******************************** 头文件 *************************************/
#include "includes.hpp"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/


/******************************* 私有函数 ************************************/


/**
 * @brief  dot_count函数
 * @param  无
 * @retval 状态码
 */
int dot_count(void)
{
	int dot_num = 0;
	int struct_element_size = 8;

	Mat img_src = imread("pcb.jpg", 0);
	Mat img_trans_byOTSU, img_erode;
	Mat lables, stats, centroids;
	Mat struct_element = getStructuringElement(MORPH_RECT, Size(struct_element_size, struct_element_size), Point(-1, -1));

	/* 反色 */
	img_src = 255 - img_src;

	/* 大津法处理图像 */
	threshold(img_src, img_trans_byOTSU, 100, 255, THRESH_OTSU);

	/* 对图像进行腐蚀处理，只保留要求的点 */
	//erode(img_trans_byOTSU, img_erode, struct_element, Point(-1, -1), 2);
	morphologyEx(img_trans_byOTSU, img_erode, MORPH_OPEN, struct_element, Point(-1, -1), 2);

	/* 连通域标记 */
	dot_num = connectedComponentsWithStats(img_erode, lables, stats, centroids, 8, CV_32S);

	/* 减去背景，并输出dot个数 */
	cout << "Dot count num is: " << dot_num - 1 << endl;

	imshow("img_src", img_src);
	imshow("img_erode", img_erode);

	/* 等待用户按键 */
	waitKey(0);

	return 0;
}

/**
 * @brief  clip_count函数
 * @param  无
 * @retval 状态码
 */
int clip_count(void)
{
	int clip_num = 0;
	int struct_element_size = 4;

	Mat img_src = imread("clip.png", 0);
	Mat img_trans_byOTSU, img_erode;
	Mat lables, stats, centroids;
	Mat struct_element = getStructuringElement(MORPH_RECT, Size(struct_element_size, struct_element_size), Point(-1, -1));

	/* 反色 */
	img_src = 255 - img_src;

	/* 大津法处理图像 */
	threshold(img_src, img_trans_byOTSU, 100, 255, THRESH_OTSU);

	/* 对图像进行开运算处理，去除噪声 */
	morphologyEx(img_trans_byOTSU, img_erode, MORPH_OPEN, struct_element, Point(-1, -1), 1);

	/* 连通域标记 */
	clip_num = connectedComponentsWithStats(img_erode, lables, stats, centroids, 8, CV_32S);

	/* 去除干扰连通域 */
	int clip_num_temp = clip_num;
	for (int i = 1; i < clip_num_temp; i++) {
		int width = stats.at<int>(i, 2);
		int height = stats.at<int>(i, 3);
		int area = stats.at<int>(i, 4);

		/* 去除尺寸比例和面积异常的干扰连通域 */
		if (height / width > 5 || area < 2000 || area > 4000) {
			clip_num--;
		}
	}

	/* 减去背景，并输出clip个数 */
	cout << "Clip count num is: " << clip_num - 1 << endl;

	imshow("img_src", img_src);
	imshow("img_erode", img_erode);

	/* 等待用户按键 */
	waitKey(0);

	return 0;
}

/*********************************END OF FILE*********************************/
