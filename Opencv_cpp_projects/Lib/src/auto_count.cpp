/******************************** ͷ�ļ� *************************************/
#include "includes.hpp"

/****************************** ˽�к궨�� ***********************************/

/******************************* ȫ�ֱ��� ************************************/

/***************************** ˽��ȫ�ֱ��� **********************************/


/******************************* ˽�к��� ************************************/


/**
 * @brief  dot_count����
 * @param  ��
 * @retval ״̬��
 */
int dot_count(void)
{
	int dot_num = 0;
	int struct_element_size = 8;

	Mat img_src = imread("pcb.jpg", 0);
	Mat img_trans_byOTSU, img_erode;
	Mat lables, stats, centroids;
	Mat struct_element = getStructuringElement(MORPH_RECT, Size(struct_element_size, struct_element_size), Point(-1, -1));

	/* ��ɫ */
	img_src = 255 - img_src;

	/* ��򷨴���ͼ�� */
	threshold(img_src, img_trans_byOTSU, 100, 255, THRESH_OTSU);

	/* ��ͼ����и�ʴ����ֻ����Ҫ��ĵ� */
	//erode(img_trans_byOTSU, img_erode, struct_element, Point(-1, -1), 2);
	morphologyEx(img_trans_byOTSU, img_erode, MORPH_OPEN, struct_element, Point(-1, -1), 2);

	/* ��ͨ���� */
	dot_num = connectedComponentsWithStats(img_erode, lables, stats, centroids, 8, CV_32S);

	/* ��ȥ�����������dot���� */
	cout << "Dot count num is: " << dot_num - 1 << endl;

	imshow("img_src", img_src);
	imshow("img_erode", img_erode);

	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

/**
 * @brief  clip_count����
 * @param  ��
 * @retval ״̬��
 */
int clip_count(void)
{
	int clip_num = 0;
	int struct_element_size = 4;

	Mat img_src = imread("clip.png", 0);
	Mat img_trans_byOTSU, img_erode;
	Mat lables, stats, centroids;
	Mat struct_element = getStructuringElement(MORPH_RECT, Size(struct_element_size, struct_element_size), Point(-1, -1));

	/* ��ɫ */
	img_src = 255 - img_src;

	/* ��򷨴���ͼ�� */
	threshold(img_src, img_trans_byOTSU, 100, 255, THRESH_OTSU);

	/* ��ͼ����п����㴦��ȥ������ */
	morphologyEx(img_trans_byOTSU, img_erode, MORPH_OPEN, struct_element, Point(-1, -1), 1);

	/* ��ͨ���� */
	clip_num = connectedComponentsWithStats(img_erode, lables, stats, centroids, 8, CV_32S);

	/* ȥ��������ͨ�� */
	int clip_num_temp = clip_num;
	for (int i = 1; i < clip_num_temp; i++) {
		int width = stats.at<int>(i, 2);
		int height = stats.at<int>(i, 3);
		int area = stats.at<int>(i, 4);

		/* ȥ���ߴ����������쳣�ĸ�����ͨ�� */
		if (height / width > 5 || area < 2000 || area > 4000) {
			clip_num--;
		}
	}

	/* ��ȥ�����������clip���� */
	cout << "Clip count num is: " << clip_num - 1 << endl;

	imshow("img_src", img_src);
	imshow("img_erode", img_erode);

	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

/*********************************END OF FILE*********************************/
