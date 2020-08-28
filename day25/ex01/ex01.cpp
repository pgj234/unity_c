#include <core.hpp>
#include <highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int exam1() {
    Mat img = imread("../res/20200818_185216.jpg", IMREAD_COLOR);

    if (img.empty()) {
        printf("image load error");
        return 1;
    }

    imshow("Display", img);
    waitKey(0);

    cout << "Hello World!\n";
    return 0;
}

int exam2_cam() {
    Mat img_color;

    VideoCapture cap(0);

    if (!cap.isOpened()) {
        printf("camera open error\n");
        return 1;
    }

    while (1) {
        cap.read(img_color);

        //if (!img_color.empty()) {
        //    printf("capture error");
        //    break;
        //}

        imshow("color", img_color);

        if (waitKey(25) >= 0) {
            break;
        }
    }

    return 0;
}

int main() {


    return exam2_cam();
}