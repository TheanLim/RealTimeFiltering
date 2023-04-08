//
//  vidDisplay.cpp
//  Project1
//
//  Created by Thean Cheat Lim on 1/13/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>  // for converting to grayscale
#include "filter.hpp"           // Converting to alternative grayscale
#include <cstring>

int main(int argc, char *argv[]) {
    cv::VideoCapture *capdev;

    // open the video device
    capdev = new cv::VideoCapture(0);
    if( !capdev->isOpened() ) {
            printf("Unable to open video device\n");
            return(-1);
    }

    // get some properties of the image
    cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                   (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    int fps = capdev->get(cv::CAP_PROP_FPS);
    printf("Expected size: %d %d\n", refS.width, refS.height);
    std::cout << "Frames per second :" << fps;

    cv::namedWindow("Video", 1); // identifies a window
    cv::Mat frame;
    cv::Mat filteredFrame;
    
    char filterKey = 'n';  // n for normal -- no filter
    bool saveVideo = false;
    cv::VideoWriter video("savedVideo.avi",                                 // filename
                          cv::VideoWriter::fourcc('M','J','P','G'),         // fourcc
                          15 ,                                             // fps
                          refS,                                             // frameSize
                          true);                                            // isColor
    
    for(;;) {
        *capdev >> frame; // get a new frame from the camera, treat as a stream
        if( frame.empty() ) {
          printf("frame is empty\n");
          break;
        }
        // Show Live video
        if (filterKey=='n') frame.copyTo(filteredFrame);  // No filtering Done
        if (filterKey=='g') {
            cvtColor(frame, filteredFrame, cv::COLOR_BGR2GRAY);
            cvtColor(filteredFrame, filteredFrame, cv::COLOR_GRAY2BGR);
        }
        if (filterKey=='h') greyscale(frame, filteredFrame);
        if (filterKey=='b') blur5x5(frame, filteredFrame);
        if (filterKey=='x'){
            sobelX3x3(frame, filteredFrame);
            cv::convertScaleAbs(filteredFrame, filteredFrame);
        }
        if (filterKey=='y'){
            sobelY3x3(frame, filteredFrame);
            cv::convertScaleAbs(filteredFrame, filteredFrame);
        }
        if (filterKey=='m'){
            cv::Mat sobelXFrame;
            cv::Mat sobelYFrame;
            sobelX3x3(frame, sobelXFrame);
            sobelY3x3(frame, sobelYFrame);
            magnitude(sobelXFrame, sobelYFrame, filteredFrame);
        }
        if (filterKey=='l') blurQuantize(frame, filteredFrame, 15);
        if (filterKey=='c') cartoon(frame, filteredFrame, 15, 20);
        if (filterKey=='a') negative(frame, filteredFrame);
        if (filterKey=='r') blurRelflect(frame, filteredFrame, 4, 5);
        
        if (saveVideo) video.write(filteredFrame);
        cv::imshow("Video", filteredFrame);
        
        // see if there is a waiting keystroke
        char key = cv::waitKey(10);
        if( key == 'q') {
            break;
        }
        if (key == 's') {
            std::string filteredFn;  // Filename
            if (filterKey=='n')filteredFn = "FrameNoFilter.png";
            if (filterKey=='g')filteredFn = "FrameGrayscale.png";
            if (filterKey=='h')filteredFn = "FrameGrayscaleAlt.png";
            if (filterKey=='b')filteredFn = "FrameGaussian.png";
            if (filterKey=='x')filteredFn = "FrameSobelX.png";
            if (filterKey=='y')filteredFn = "FrameSobelY.png";
            if (filterKey=='m')filteredFn = "FrameMagnitude.png";
            if (filterKey=='l')filteredFn = "FrameQuantized.png";
            if (filterKey=='c')filteredFn = "FrameCartoon.png";
            if (filterKey=='a')filteredFn = "FrameNegative.png";
            if (filterKey=='r')filteredFn = "FrameBlurReflect.png";
            
            std::cout << "Add a caption to the filtered image. Leave it blank if you don't want to: \n";
            std::string caption;
            getline(std::cin, caption);
            if (!caption.empty()){
                cv::putText(filteredFrame,              //target image
                            caption,                    //text
                            cv::Point(0, filteredFrame.rows-20), //bottom-left position
                            cv::FONT_HERSHEY_COMPLEX,   // fontFace
                            2.0,                        // fontScale
                            CV_RGB(255, 255, 255),      // color
                            2,                          // thickness (default 1)
                            cv::FILLED                  // lineType
                            );
            }
            imwrite("FrameDefault.png", frame);         // Always save the orig display
            imwrite(filteredFn, filteredFrame);         // Saves the filtered Frame
            std::cout << "Done saving frames\n";
        }

        // Filter key
        if (strchr("nghbxymlcavr", key)){ /*https:stackoverflow.com/a/19548575/19481647*/
            if (key =='v'){
                saveVideo = true;
            } else {
                filterKey = key;
            }
        }
    }

    delete capdev;
    return(0);
}
