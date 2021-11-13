/******************************** ͷ�ļ� *************************************/
#include "includes.hpp"

/****************************** ˽�к궨�� ***********************************/

/******************************* ȫ�ֱ��� ************************************/

/***************************** ˽��ȫ�ֱ��� **********************************/


/******************************* ˽�к��� ************************************/


/**
 * @brief  ͼ����ת���ű任
 * @param  ��
 * @retval ��
 */
int img_rotate_scale(void)
{
	Mat img_src = imread("lena.jpg");
	Mat	img_trans;

	float angle = -10.0;
	float scale = 1;	/* ���ű��� */

	Point2f img_center(img_src.cols * 0.5, img_src.rows * 0.5);

	Mat affine_matrix = getRotationMatrix2D(img_center, angle, scale);

	warpAffine(img_src, img_trans, affine_matrix, img_src.size());

	imshow("img_src", img_src);
	imshow("img_trans", img_trans);
	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

/**
 * @brief  ͼ�����任
 * @param  ��
 * @retval ��
 */
int img_affine(void)
{
	Mat img_src = imread("lena.jpg");
	Mat	img_trans;

	Point2f pt_src[] = {
						Point2f(200, 200),
						Point2f(250, 200),
						Point2f(200, 100)
	};

	Point2f pt_trans[] = {
						Point2f(300, 100),
						Point2f(300, 50),
						Point2f(200, 100)
	};

	Mat affine_matrix = getAffineTransform(pt_src, pt_trans);

	warpAffine(img_src, img_trans, affine_matrix, img_src.size());

	imshow("img_src", img_src);
	imshow("img_trans", img_trans);
	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

/**
 * @brief  ͼ��ͶӰ�任
 * @param  ��
 * @retval ��
 */
int img_projection(void)
{
	Mat img_src = imread("lena.jpg");
	Mat	img_trans;

	Point2f pts1[] = {
						Point2f(150, 150),
						Point2f(150, 300),
						Point2f(350, 300),
						Point2f(350, 150),
	};

	Point2f pts2[] = {
						Point2f(200, 150),
						Point2f(200, 300),
						Point2f(340, 270),
						Point2f(340, 180),
	};

	Mat perspective_matrix = getPerspectiveTransform(pts1, pts2);

	warpPerspective(img_src, img_trans, perspective_matrix, img_src.size());

	imshow("img_src", img_src);
	imshow("img_trans", img_trans);
	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

/**
 * @brief  ͼ���Զ�����
 * @param  ��
 * @retval ��
 */
int img_correct(void)
{
	float angle_cor;	/* ������ת���� */
	float scale_cor;	/* �������ű��� */

	Mat img_src = imread("lena_warp.jpg");
	Mat img_cpy = img_src.clone();
	Mat	img_trans;
	Mat img_gray;
	Mat contours;

	cvtColor(img_src, img_gray, COLOR_BGR2GRAY);

	/* ��Ե��� */
	Canny(img_gray, contours, 150, 300);

	/* Hough�任��� */
	vector<Vec2f> lines;
	HoughLines(contours, lines, 1.0, CV_PI / 180, 150, 0, 0 , 0, CV_PI / 2);

	/* �ҳ�ͼ����Ҫ�����ĽǶȼ����ű��� */
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		static float rho_min = lines[0][0];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));  //�Ѹ�����ת��������
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(img_cpy, pt1, pt2, Scalar(255, 0, 0), 1, CV_AA);
		if (rho < rho_min) {
			rho_min = rho;
			if (theta < CV_PI / 4) {
				angle_cor = theta / CV_PI * 180;
			}
			else {
				angle_cor = -(90 - theta / CV_PI * 180);
			}
			scale_cor = img_src.rows / (rho / sin(theta) / cos(theta));
			cout << "angle_cor:" << angle_cor << ' ' << "scale_cor:" << scale_cor << endl;
		}
		cout << "rho:" << rho << "theta" << theta << endl;
	}

	Point2f img_center(img_src.cols * 0.5, img_src.rows * 0.5);
	Mat affine_matrix = getRotationMatrix2D(img_center, angle_cor, scale_cor);
	warpAffine(img_src, img_trans, affine_matrix, img_src.size());

	imshow("img_src", img_src);
	imshow("img_cpy", img_cpy);
	imshow("contours", contours);
	imshow("img_trans", img_trans);
	/* �ȴ��û����� */
	waitKey(0);

	return 0;
}

 /*********************************END OF FILE*********************************/
