/******************************** ͷ�ļ� *************************************/
#include "includes.h"

/****************************** ˽�к궨�� ***********************************/

/******************************* ȫ�ֱ��� ************************************/

/***************************** ˽��ȫ�ֱ��� **********************************/


/******************************* ˽�к��� ************************************/


/**
 * @brief  ͼ���ֵ��
 * @param  ��
 * @retval ״̬��
 */
int img_binary(void)
{
	Mat img_src = imread("sonnet_for_lena.png", 0);
	Mat img_trans_byBINARY;
	Mat img_trans_byOTSU;
	Mat img_trans_byGAUSSIAN;

	threshold(img_src, img_trans_byBINARY, 100, 255, THRESH_BINARY);
	threshold(img_src, img_trans_byOTSU, 100, 255, THRESH_OTSU);

	adaptiveThreshold(img_src, img_trans_byGAUSSIAN, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);

	imshow("img_src", img_src);
	imshow("img_trans_byBINARY", img_trans_byBINARY);
	imshow("img_trans_byOTSU", img_trans_byOTSU);
	imshow("img_trans_byGAUSSIAN", img_trans_byGAUSSIAN);

	/* �ȴ��û����� */
	waitKey(0);

	destroyAllWindows();

	return 0;
}

/*********************************END OF FILE*********************************/
