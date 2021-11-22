#ifndef __INCLUDESE_HPP
#define	__INCLUDESE_HPP

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
int cv_erode(void);
int cv_bounding(void);
int dot_count(void);
int clip_count(void);
int cv_blur(void);
int cv_sobel(void);
int skin_ps(void);
int cv_canny(void);
int img_rotate_scale(void);
int img_affine(void);
int img_projection(void);
int img_correct(void);
int img_rotate_cor(void);
int img_houghlines(void);
int img_houghlines_p(void);
int cv_findhole(void);
int cv_findchip(void);
int cv_findcup(void);

#endif /* __INCLUDESE_HPP */
