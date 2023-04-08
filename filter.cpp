////
////  filter.cpp
////  Project1
////
////  Created by Thean Cheat Lim on 1/15/23.
////
//
//#include "filter.hpp"
//#include <opencv2/opencv.hpp>
//#include <cmath>
//#include <stdio.h>
//
//int greyscale(cv::Mat &src, cv::Mat &dst){
//    dst = cv::Mat::zeros(src.size(), src.type());
//    for(int i=0; i<src.rows; i++){
//        // Src pointer
//        cv::Vec3b *sptr = src.ptr<cv::Vec3b>(i);
//        // Destination pointer
//        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
//        //loop over the columns
//        for(int j=0; j<src.cols; j++){
//            //average each color channel
//            uchar avgColor =(sptr[j][0]+sptr[j][1]+sptr[j][2])/3;
//            dptr[j][0] = avgColor;
//            dptr[j][1] = avgColor;
//            dptr[j][2] = avgColor;
//        }
//    }
//    return 0;
//}
//
//int blur5x5(cv::Mat &src, cv::Mat &dst){
//    // Filter [1 2 4 2 1]
//    src.copyTo(dst);  // Keep the orig values as if if not modified
//    
//    // Row 1D
//    for(int i=0; i<src.rows; i++){
//        cv::Vec3b *sptr = src.ptr<cv::Vec3b>(i);
//        // Destination pointer
//        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
//        for(int j=2; j<src.cols-2; j++){
//            for(int c=0;c<3;c++){
//                dptr[j][c] =
//                (
//                 1*sptr[j-2][c]
//                 +2*sptr[j-1][c]
//                 +4*sptr[j][c]
//                 +2*sptr[j+1][c]
//                 +1*sptr[j+2][c]
//                )/10;
//            }
//        }
//    }
//    
//    cv::Mat temp;
//    dst.copyTo(temp);
//    // Column 1D
//    for(int j=0; j<src.cols; j++){
//        for(int i=2; i<src.rows-2; i++){
//            for(int c=0;c<3;c++){
//                dst.at<cv::Vec3b>(i, j)[c] =
//                (
//                 1*temp.at<cv::Vec3b>(i-2, j)[c]
//                 +2*temp.at<cv::Vec3b>(i-1, j)[c]
//                 +4*temp.at<cv::Vec3b>(i, j)[c]
//                 +2*temp.at<cv::Vec3b>(i+1, j)[c]
//                 +1*temp.at<cv::Vec3b>(i+2, j)[c]
//                 )/10;
//            }
//        }
//    }
//    
//    return 0;
//}
//
//int sobelX3x3(cv::Mat &src, cv::Mat &dst){
//    // Positive Right
//    //    [-1, 0, 1]
//    //    [-2, 0, 2]
//    //    [-1, 0, 1]
//    //
//    dst = cv::Mat::zeros(src.size(), CV_16SC3); // signed short data type
//    // Row 1D
//    // [-1, 0, 1]
//    for(int i=0; i<src.rows; i++){
//        cv::Vec3b *sptr = src.ptr<cv::Vec3b>(i);
//        // Destination pointer
//        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);
//        for(int j=1; j<src.cols-1; j++){
//            for(int c=0;c<3;c++){
//                dptr[j][c] =
//                (
//                 -1*sptr[j-1][c]
//                 +1*sptr[j+1][c]
//                );
//            }
//        }
//    }
//    
//    cv::Mat temp;
//    dst.copyTo(temp);
//    
//    // Column 1D
//    //    [1]
//    //    [2]
//    //    [1]
//    for(int j=0; j<src.cols; j++){
//        for(int i=1; i<src.rows-1; i++){
//            for(int c=0;c<3;c++){
//                dst.at<cv::Vec3s>(i, j)[c] =
//                (
//                 1*temp.at<cv::Vec3s>(i-1, j)[c]
//                 +2*temp.at<cv::Vec3s>(i, j)[c]
//                 +1*temp.at<cv::Vec3s>(i+1, j)[c]
//                 )/4;
//            }
//        }
//    }
//    
//     return 0;
//}
//
//int sobelY3x3(cv::Mat &src, cv::Mat &dst){
//    // Positive Up
//    //  [ 1 2 1]
//    //  [ 0 0 0]
//    //  [ -1 -2 -1]
//    dst = cv::Mat::zeros(src.size(), CV_16SC3); // signed short data type
//    
//    // Row 1D
//    // [1, 2, 1]
//    for(int i=0; i<src.rows; i++){
//        cv::Vec3b *sptr = src.ptr<cv::Vec3b>(i);
//        // Destination pointer
//        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);
//        for(int j=1; j<src.cols-1; j++){
//            for(int c=0;c<3;c++){
//                dptr[j][c] =
//                (
//                 1*sptr[j-1][c]
//                 +2*sptr[j][c]
//                 +1*sptr[j+1][c]
//                )/4;
//            }
//        }
//    }
//    
//    cv::Mat temp;
//    dst.copyTo(temp);
//    // Column 1D
//    //    [+1]
//    //    [0]
//    //    [-1]
//    for(int j=0; j<src.cols; j++){
//        for(int i=1; i<src.rows-1; i++){
//            for(int c=0;c<3;c++){
//                dst.at<cv::Vec3s>(i, j)[c] =
//                (
//                 1*temp.at<cv::Vec3s>(i-1, j)[c]
//                 -1*temp.at<cv::Vec3s>(i+1, j)[c]
//                 );
//            }
//        }
//    }
//     return 0;
//}
//
//int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst){
//    dst = cv::Mat::zeros(sx.size(), CV_8UC3); // unsigned short data type
//    for(int i=0;i<sx.rows;i++){
//        // sx, sy pointers
//        cv::Vec3s *sxptr = sx.ptr<cv::Vec3s>(i);
//        cv::Vec3s *syptr = sy.ptr<cv::Vec3s>(i);
//        // destination pointer
//        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
//        
//        for(int j=0;j<sx.cols;j++){
//            for(int c=0;c<3;c++){
//                dptr[j][c] = sqrt(pow(sxptr[j][c], 2)+pow(syptr[j][c], 2));
//            }
//       }
//     }
//    return 0;
//}
//int blurQuantize(cv::Mat &src, cv::Mat &dst, int levels){
//    src.copyTo(dst);
//    int b = 255/levels;
//    for(int i=0;i<dst.rows;i++){
//        //Destination pointer
//        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
//        for(int j=0;j<dst.cols;j++){
//            for(int c=0;c<3;c++){
//                dptr[j][c] = dptr[j][c]/b;
//                dptr[j][c] = dptr[j][c]*b;
//            }
//        }
//    }
//    return 0;
//}
//int cartoon(cv::Mat &src, cv::Mat&dst, int levels, int magThreshold){
//    cv::Mat sobelXSrc;
//    cv::Mat sobelYSrc;
//    cv::Mat gradMag;
//    sobelX3x3(src, sobelXSrc);
//    sobelY3x3(src, sobelYSrc);
//    magnitude(sobelXSrc, sobelYSrc, gradMag);
//    blurQuantize(src, dst, levels);
//    for(int i=0;i<dst.rows;i++){
//        //Destination pointer
//        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
//        // Gradient Magnitude pointer
//        cv::Vec3b *gptr = gradMag.ptr<cv::Vec3b>(i);
//        
//        for(int j=0;j<dst.cols;j++){
//            for(int c=0;c<3;c++){
//                if(gptr[j][c]>magThreshold) dptr[j][c] = 0;
//            }
//        }
//    }
//    
//    return 0;
//}
//
//int negative(cv::Mat &src, cv::Mat &dst){
//    src.copyTo(dst);
//    for(int i=0;i<src.rows;i++){
//        // destination pointer
//        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
//        for(int j=0;j<src.cols;j++){
//            for(int c=0;c<3;c++){
//                dptr[j][c] = 255 - dptr[j][c];
//            }
//       }
//     }
//    return 0;
//}
//
//int blurRelflect(cv::Mat &src, cv::Mat&dst, int width, int height){
//    // padding
//    int top = height/2;
//    int bottom = top;
//    int left = width/2;
//    int right = left;
//    
//    cv::Mat temp;
//    copyMakeBorder(src, temp, top, bottom, left, right, cv::BORDER_REPLICATE);
//    src.copyTo(dst);
//    
//    // for channel 0,1,2
//    int box0=0;
//    int box1=0;
//    int box2=0;
//    for(int i=0; i<dst.rows; i++){
//        for(int j=0; j<dst.cols; j++){
//            if (j==0){
//                box0=0;
//                box1=0;
//                box2=0;
//                for(int ki = i; ki<i+height; ki++){
//                    for(int kj = j; kj<j+width; kj++){
//                        box0 += temp.at<cv::Vec3b>(ki, kj)[0];
//                        box1 += temp.at<cv::Vec3b>(ki, kj)[1];
//                        box2 += temp.at<cv::Vec3b>(ki, kj)[2];
//                    }
//                }
//            }
//            // Optimization part - to make it faster
//            // Since we move from left->right, let's dont recompute the same columns
//            // Drop the left most and add the right most
//            if (j!=0){
//                int left_idx = j-1;
//                int right_idx = j+width-1;
//                for(int ki = i; ki<i+height; ki++){
//                    box0 = box0 - temp.at<cv::Vec3b>(ki, left_idx)[0] + temp.at<cv::Vec3b>(ki, right_idx)[0];
//                    box1 = box1 - temp.at<cv::Vec3b>(ki, left_idx)[1] + temp.at<cv::Vec3b>(ki, right_idx)[1];
//                    box2 = box2 - temp.at<cv::Vec3b>(ki, left_idx)[2] + temp.at<cv::Vec3b>(ki, right_idx)[2];
//                }
//            }
//            dst.at<cv::Vec3b>(i, j)[0] = box0/(width*height);
//            dst.at<cv::Vec3b>(i, j)[1] = box1/(width*height);
//            dst.at<cv::Vec3b>(i, j)[2] = box2/(width*height);
//        }
//    }
//
//    return 0;
//}
