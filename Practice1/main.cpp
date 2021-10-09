#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()
{
	cv:: Mat srcImg = imread("E:/cProject/Practice1/lena.jpg");

	int width = srcImg.cols;
	int high = srcImg.rows;

	for (int j = 0; j < high; j++) {
		for (int i = 0; i < width; i++) {
			uint8_t avg = (srcImg.at<Vec3b>(j, i)[0] + srcImg.at<Vec3b>(j, i)[1] + srcImg.at<Vec3b>(j, i)[2]) / 3;
			srcImg.at<Vec3b>(j, i)[0] = avg;
			srcImg.at<Vec3b>(j, i)[1] = avg;
			srcImg.at<Vec3b>(j, i)[2] = avg;
		}
	}
	imshow("transImg", srcImg);
	std::cout << "ok";
	/* 等待用户按键 */
	waitKey(0);

	return 0;
}