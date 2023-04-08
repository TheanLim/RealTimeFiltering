//
//  filter.hpp
//  Project1
//
//  Created by Thean Cheat Lim on 1/15/23.
//

#ifndef filter_hpp
#define filter_hpp

#include <opencv2/opencv.hpp>
#include <stdio.h>

int greyscale(cv::Mat &src, cv::Mat &dst);
int blur5x5(cv::Mat &src, cv::Mat &dst);
int sobelX3x3(cv::Mat &src, cv::Mat &dst);
int sobelY3x3(cv::Mat &src, cv::Mat &dst);
int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst);
int blurQuantize(cv::Mat &src, cv::Mat &dst, int levels);
int cartoon(cv::Mat &src, cv::Mat&dst, int levels, int magThreshold);
int negative(cv::Mat &src, cv::Mat&dst);
int blurRelflect(cv::Mat &src, cv::Mat&dst, int width, int height);

#endif /* filter_hpp */
