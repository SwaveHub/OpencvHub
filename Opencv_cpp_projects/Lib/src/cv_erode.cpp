/******************************** ͷ�ļ� *************************************/
#include "includes.hpp"

/****************************** ˽�к궨�� ***********************************/

/******************************* ȫ�ֱ��� ************************************/

/***************************** ˽��ȫ�ֱ��� **********************************/


/******************************* ˽�к��� ************************************/


/**
 * @brief  cv_erode����
 * @param  ��
 * @retval ״̬��
 */
int cv_erode(void)
{
	int struct_element_size = 3;

	Mat img_src = imread("coin.png", 0);
	Mat img_trans_byBINARY;
	Mat img_erode;
	Mat img_dilate;
	Mat img_open;
	Mat img_close;

	Mat struct_element = getStructuringElement(MORPH_RECT, Size(struct_element_size, struct_element_size), Point(-1, -1));

	threshold(img_src, img_trans_byBINARY, 100, 255, THRESH_BINARY);
	imshow("img_trans_byBINARY", img_trans_byBINARY);

	erode(img_trans_byBINARY, img_erode, struct_element);
	imshow("img_erode", img_erode);

	dilate(img_trans_byBINARY, img_dilate, struct_element);
	imshow("img_dilate", img_dilate);

	morphologyEx(img_trans_byBINARY, img_open, MORPH_OPEN, struct_element);
	imshow("img_open", img_open);

	morphologyEx(img_trans_byBINARY, img_close, MORPH_CLOSE, struct_element);
	imshow("img_close", img_close);

	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

/*********************************END OF FILE*********************************/
