#ifndef __INCLUDESE_H
#define	__INCLUDESE_H

/******************************** ͷ�ļ� *************************************/
#include <opencv2/opencv.hpp>
#include <iostream>

/******************************** �궨�� *************************************/


/***************************** ȫ�ֱ������� **********************************/
using namespace cv;
using namespace std;

/******************************* �������� ************************************/
int img_show(void);
int cv_draw(void);
int histgram_disp(void);
int channel_show(void);
int video_capture(void);
int skin_detect(void);
int img_binary(void);
int cv_callback(void);

#endif /* __INCLUDESE_H */
