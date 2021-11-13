/******************************** 头文件 *************************************/
#include "includes.hpp"

/****************************** 私有宏定义 ***********************************/

/******************************* 全局变量 ************************************/

/***************************** 私有全局变量 **********************************/


/******************************* 私有函数 ************************************/


/**
 * @brief  cv_bounding函数
 * @param  无
 * @retval 状态码
 */
int cv_bounding(void)
{
	int struct_element_size = 3;
	int coin_num = 0;

	Mat img_src = imread("coin.png", 0);
	Mat img_trans_byBINARY;
	Mat lables, stats, centroids;
	Mat struct_element = getStructuringElement(MORPH_RECT, Size(struct_element_size, struct_element_size), Point(-1, -1));

	/* 灰度图像二值化处理并进行开运算去除噪声 */
	threshold(img_src, img_trans_byBINARY, 100, 255, THRESH_BINARY);
	morphologyEx(img_trans_byBINARY, img_trans_byBINARY, MORPH_OPEN, struct_element);

	/* 连通域标记 */
	coin_num = connectedComponentsWithStats(img_trans_byBINARY, lables, stats, centroids, 8, CV_32S);

	/* 减去背景，并输出硬币个数 */
	cout << "Coin count num is: " << coin_num - 1 << endl;

	/* 为连通域绘制外接四边形 */
	for (int i = 1; i < coin_num; i++) {
		Rect bounding_box;

		bounding_box.x = stats.at<int>(i, 0);
		bounding_box.y = stats.at<int>(i, 1);
		bounding_box.width = stats.at<int>(i, 2);
		bounding_box.height = stats.at<int>(i, 3);

		rectangle(img_trans_byBINARY, bounding_box, 255 , 1, 8, 0);
	}

	imshow("img_trans_byBINARY", img_trans_byBINARY);

	/* 等待用户按键 */
	waitKey(0);

	return 0;
}

/*********************************END OF FILE*********************************/
