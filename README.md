# RealTimeFiltering

## Description
This project mainly focuses on manipulating images in OpenCV. Specifically, I’ve implemented several commonly seen filters, such as the grayscale, Gaussian, Negative, and Sobel Filters. I have also implemented codes to create quantized images and gradient-magnitude images. Combining the two gives us a cartoonized image. Moreover, I have also added captions to images, implemented OpenCV blur() filters with Reflection padding, and added the capability of saving un/filtered frames into videos.

## Demo
### Grayscale 
<img src="/images/FrameGrayscale.png" width="800" height="500">

### Gaussian Blur 
<img src="/images/FrameGaussian.png" width="800" height="500">

### Gradient magnitude
<img src="/images/FrameMagnitude.png" width="800" height="500">

### Negative
<img src="/images/FrameNegative.png" width="800" height="500">

### Quantized
<img src="/images/FrameQuantized.png" width="800" height="500">

### Cartoonized
<img src="/images/FrameCartoon.png" width="800" height="500">

## OS and IDE used
OS:
MacOS Ventura 13.0.1 (22A400)

IDE:
XCode

## Instructions:
Run vidDisplay.cpp
Some useful hotkeys:
- n = No Filtering
- s = Save image
- q = Quit program
- v = Save Video. Need to press 'q' to stop the video
- g = grayscale image
- h = alternate grayscale image
- b = Gaussian Filter Blurred image
- x = Sobel X filtered image
- y = Sobel Y filtered image
- m = Gradient magnitude image
- l = Quantized image
- c = Cartoonized image
- a = Negative image
- r = Alternative Blurred image

To run imgDisplay.cpp:
1. Uncomment the main function.
2. Comment out vidDisplay.cpp's main function.
3. Store cuteHusky.jpeg at the same directory as the imgDisplay.cpp
