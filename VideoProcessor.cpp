#include "VideoProcessor.h"
#include "opencv2/opencv.hpp"

void VideoProcessor::run()
{
    std::vector<cv::Mat> frameList;
    cv::VideoCapture cap("/home/marco/Videos/vela.mp4");

    if(!cap.isOpened())
        return;

    int numberOfFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
    //for(int i = 0; i < numberOfFrames; i++)
    //{
    //    cv::Mat frame;
    //    cap >> frame;
    //    frameList.push_back(frame);
    //}

    int counter = 0;

    cv::Mat frame;
    for(;;)
    {
        cap >> frame;

        cv::Mat frameBW(frame.size(), CV_BGR2GRAY);
        cv::cvtColor(frame, frameBW, CV_BGR2GRAY);

        //int offset = 80;
        //cv::Rect roi = {frameBW.cols/2 + offset, 0, frameBW.cols/2 - offset, frameBW.rows};
        //cv::Mat partial = frameBW(roi);
        //cv::flip(partial , partial , 0);
        //partial.copyTo(frameBW(roi));

        cap.set(CV_CAP_PROP_POS_FRAMES, numberOfFrames/2 - counter - 1);

        std::cout << counter << std::endl;

        int offset = 80;
        cv::Rect roi = {frameBW.cols/2 + offset, 0, frameBW.cols/2 - offset, frameBW.rows};
        cv::Mat revertedFrame;
        cap >> revertedFrame;
        cv::Mat revertedFrameBW(frame.size(), CV_BGR2GRAY);
        cv::cvtColor(revertedFrame, revertedFrameBW, CV_BGR2GRAY);
        cv::Mat partial = revertedFrameBW(roi);
        //cv::flip(partial , partial , 2);
        partial.copyTo(frameBW(roi));

        cap.set(CV_CAP_PROP_POS_FRAMES, ++counter);

        //cv::Mat new_image = cv::Mat::zeros( frameBW.size(), frameBW.type() );

        //double alpha = 2.0; /*< Simple contrast control */
        //    int beta = 0;       /*< Simple brightness control */
        //    for( int y = 0; y < frameBW.rows; y++ ) {
        //        for( int x = 0; x < frameBW.cols; x++ ) {
        //            for( int c = 0; c < frameBW.channels(); c++ ) {
        //                new_image.at<cv::Vec3b>(y,x)[c] =
        //                  cv::saturate_cast<uchar>( alpha*frameBW.at<cv::Vec3b>(y,x)[c] + beta );
        //            }
        //        }
        //    }

        cv::imshow("Monitor", frameBW);

        if(cv::waitKey(30) >= 0) break;
    }
}
