#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main (int, char**) {
    cv::VideoCapture cvap;
    cv::Mat image;

    // works on D-Linke CDS-932L
    const std::string strm_addr = 
        "rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2";

    // open vid strm and confirm
    if (!cvap.open(strm_addr)) {
        cout << "Error opening video stream" << endl;
        return -1;
    }

    for (;;) {
        if (!cvap.read(image)) {
            cout << "No Frame" << endl;
            waitKey();
        }

        imshow("Output Window", image);
        if (waitKey(1) >= 0) break;
    }

}


