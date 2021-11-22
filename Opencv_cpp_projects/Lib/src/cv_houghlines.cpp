/******************************** ͷ�ļ� *************************************/
#include "includes.hpp"

/****************************** ˽�к궨�� ***********************************/

/******************************* ȫ�ֱ��� ************************************/

/***************************** ˽��ȫ�ֱ��� **********************************/


/******************************* ˽�к��� ************************************/


/**
 * @brief  ͼ����ת����
 * @param  ��
 * @retval ��
 */
int img_rotate_cor(void)
{
	Mat img_src = imread("lena.jpg");
	Mat	img_trans;

	float angle = -10.0;
	float scale = 1;	/* ���ű��� */

	Point2f img_center(img_src.cols * 0.5, img_src.rows * 0.5);

	Mat affine_matrix = getRotationMatrix2D(img_center, angle, scale);

	/* ��ȡ����ı��� */
	Rect bbox = RotatedRect(img_center, img_src.size(), angle).boundingRect();

	affine_matrix.at<double>(0, 2) += bbox.width / 2.0 - img_center.x;
	affine_matrix.at<double>(1, 2) += bbox.height / 2.0 - img_center.y;

	warpAffine(img_src, img_trans, affine_matrix, bbox.size());

	imshow("img_src", img_src);
	imshow("img_trans", img_trans);
	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

/**
 * @brief  ����ֱ�߼��
 * @param  ��
 * @retval ��
 */
int img_houghlines(void)
{
	Mat img_src = imread("component.jpg");
	Mat img_gray;
	Mat contours;

	cvtColor(img_src, img_gray, COLOR_BGR2GRAY);

	/* ��˹ȥ�� */
	GaussianBlur(img_gray, img_gray, Size(3, 3), 0, 0);

	/* ��Ե��� */
	Canny(img_gray, contours, 150, 300);

	/* Hough�任��� */
	vector<Vec2f> lines;
	HoughLines(contours, lines, 1.0, CV_PI / 180, 120, 0, 0, 0, CV_PI);

	/* �ҳ�ֱ��  */
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));  //�Ѹ�����ת��������
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(img_src, pt1, pt2, Scalar(0, 255, 255), 1, CV_AA);
	}
	cout << "lines:" << lines.size() << endl;

	imshow("img_src", img_src);
	imshow("contours", contours);
	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

/**
 * @brief  ����ֱ�߸��ʼ��
 * @param  ��
 * @retval ��
 */
int img_houghlines_p(void)
{
	Mat img_src = imread("component.jpg");
	Mat img_gray;
	Mat contours;

	cvtColor(img_src, img_gray, COLOR_BGR2GRAY);

	/* ��˹ȥ�� */
	GaussianBlur(img_gray, img_gray, Size(3, 3), 0, 0);

	/* ��Ե��� */
	Canny(img_gray, contours, 150, 250);

	/* Hough�任��� */
	vector<Vec4i> lines;
	HoughLinesP(contours, lines, 1.0, CV_PI / 180, 50, 50, 25);

	/* �ҳ�ֱ�� */
	for (size_t i = 0; i < lines.size(); i++) {
		Point pt1, pt2;
		pt1.x = lines[i][0];
		pt1.y = lines[i][1];
		pt2.x = lines[i][2];
		pt2.y = lines[i][3];
		line(img_src, pt1, pt2, Scalar(0, 255, 255), 1, CV_AA);
	}
	cout << "lines:" << lines.size() << endl;

	imshow("img_src", img_src);
	imshow("contours", contours);
	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

 /*********************************END OF FILE*********************************/
