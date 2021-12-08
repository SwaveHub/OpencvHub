/******************************** ͷ�ļ� *************************************/
#include "includes.hpp"

/****************************** ˽�к궨�� ***********************************/

/******************************* ȫ�ֱ��� ************************************/

/***************************** ˽��ȫ�ֱ��� **********************************/


/******************************* ˽�к��� ************************************/


/**
 * @brief  hog����ʵ��
 * @param	Mat img_src,	����ԭͼ��
 *			float *hist,	���hog������������
 *			int block_size,	�ֿ��С = block_size * block_size
 *			int angle_div��	�Ƕ���������
 * @retval ƥ���
 */
int cv_hog(Mat src, float* hist, int block_size, int angle_div)
{
	int full_angle = 360;
	int width = src.cols;
	int height = src.rows;

	int n_x = width / block_size;
	int n_y = height / block_size;
	int bins = n_x * n_y * angle_div;

	/* �����ݶȼ��Ƕ� */
	Mat grad_x, grad_y;
	Mat mag, angle;

	Sobel(src, grad_x, CV_32F, 1, 0, 1);
	Sobel(src, grad_y, CV_32F, 0, 1, 1);

	cartToPolar(grad_x, grad_y, mag, angle, true);

	for (int m = 0; m < n_y * block_size; m++) {
		for (int n = 0; n < n_x * block_size; n++) {
			int block_no = (n_x * (m / block_size) + n / block_size);
			int n_hist = block_no * angle_div + angle.at<float>(m, n) / (full_angle / angle_div);
			hist[n_hist] += 1;
		}
	}
	return 0;
}

/**
 * @brief  hog����ʵ��
 * @param	Mat img_src,	����ԭͼ��
 *			Mat img_ref,	��Ҫƥ���Ŀ��ͼ��
 *			int block_size,	�ֿ��С = block_size * block_size
 *			int angle_div��	�Ƕ���������	
 * @retval ƥ���
 */
float cv_hog_match(Mat img_src, Mat img_ref, int block_size, int angle_div)
{
	float rho = 0;	/* ���ƶ� */
	int full_angle = 360;
	int src_width = img_src.cols;
	int src_height = img_src.rows;
	int ref_width = img_ref.cols;
	int ref_height = img_ref.rows;

	int src_n_x = src_width / block_size;
	int src_n_y = src_height / block_size;
	int src_bins = src_n_x * src_n_y * angle_div;

	int ref_n_x = ref_width / block_size;
	int ref_n_y = ref_height / block_size;
	int ref_bins = ref_n_x * ref_n_y * angle_div;

	float* src_hist = new float[src_bins];
	memset(src_hist, 0, sizeof(float) * src_bins);
	float* ref_hist = new float[ref_bins];
	memset(ref_hist, 0, sizeof(float) * ref_bins);

	cv_hog(img_src, src_hist, block_size, angle_div);
	cv_hog(img_ref, ref_hist, block_size, angle_div);

	/* �˰汾�Ƚϵ�������ͬ����С��ͼ������ƶ� */
	long long square_sum = 0;
	for (int i = 0; i < src_bins && i < ref_bins; i++) {
		square_sum += pow((src_hist[i] - ref_hist[i]), 2);
	}
	rho = sqrt(square_sum);

	/* �˰汾�Ƚϵ�������ͬ����С��ͼ������ƶ�����������Χ */
	//float err = 0;
	//long long square_sum = 0 , temp = 0;
	//float euclidean_dis = 0;
	//for (int i = 0; i < src_bins && i < ref_bins; i++) {
	//	square_sum += pow(abs(src_hist[i] - ref_hist[i]) <= err ? 0 : abs(src_hist[i] - ref_hist[i]), 2);
	//}
	//euclidean_dis = sqrt(square_sum);
	//rho = euclidean_dis;

	delete[] src_hist;
	delete[] ref_hist;

	return rho;
}

/*********************************END OF FILE*********************************/
