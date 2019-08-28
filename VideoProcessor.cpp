#include "VideoProcessor.h"
#include "opencv2/opencv.hpp"

void VideoProcessor::run()
{
    cv::VideoCapture cap(0);

    if(!cap.isOpened())
        return;

    cv::Mat frame;
    for(;;)
    {
        cap >> frame;
        cv::imshow("Monitor", frame);

        if(cv::waitKey(30) >= 0) break;
    }
}
