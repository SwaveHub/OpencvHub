#ifndef __INCLUDESE_H
#define	__INCLUDESE_H

/******************************** 头文件 *************************************/
#include <opencv2/opencv.hpp>
#include <iostream>

/******************************** 宏定义 *************************************/


/***************************** 全局变量声明 **********************************/
using namespace cv;
using namespace std;

/******************************* 函数声明 ************************************/
int img_show(void);
int cv_draw(void);
int histgram_disp(void);
int channel_show(void);
int video_capture(void);
int skin_detect(void);
int img_binary(void);
int cv_callback(void);

#endif /* __INCLUDESE_H */
