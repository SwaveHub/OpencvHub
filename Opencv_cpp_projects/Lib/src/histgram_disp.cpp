/******************************** ͷ�ļ� *************************************/
#include "includes.hpp"

/****************************** ˽�к궨�� ***********************************/

/******************************* ȫ�ֱ��� ************************************/

/***************************** ˽��ȫ�ֱ��� **********************************/


/******************************* ˽�к��� ************************************/


/**
 * @brief  ����ֱ��ͼ
 * @param  ��
 * @retval ��
 */
int histgram_disp(void)
{
	float histgram[256] = { 0 };
	Mat srcImg = imread("lena.jpg", 0);
	Mat dispHistgram = Mat::zeros(300, 300, CV_8UC3);

	int width = srcImg.cols;
	int height = srcImg.rows;
	float maxHeight = 0;

	/* ͳ�ƻҶ�ֵ���� */
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			uint8_t index = srcImg.at<uchar>(j, i);
			histgram[index] += 1.0 / (width * height);
			maxHeight = histgram[index] > maxHeight ? histgram[index] : maxHeight;
		}
	}

	/* ��ʾֱ��ͼ */
	for (int i = 0; i < 256; i++) {
		line(dispHistgram, Point(i, 300), Point(i, 300 - (int)(histgram[i] / maxHeight * 300)), CV_RGB(255, 0, 0), 1, 8, 0);
	}

	imshow("srcImg", srcImg);
	imshow("dispHistgram", dispHistgram);

	/* �ȴ��û����� */
	waitKey(0);

	destroyAllWindows();

	return 0;
}

/*********************************END OF FILE*********************************/
