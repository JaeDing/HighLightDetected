//#include <QtCore/QCoreApplication>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "iostream"

using namespace std;
using namespace cv;

//声明全局变量
Mat mat;
int g_nTrackbarValue;
const int g_nTrackbarMaxValue = 255;     //滑动条最大值

//声明回掉函数
void on_Trackbar(int val, void*);

int main()
{
    Mat src;
    src = imread("img1.bmp");
    resize(src,src,Size(600,400));
    if(src.empty())
    {

        cout << "empty" << endl;
        return -1;
    }
//    namedWindow("src",0);
//    cvResizeWindow("src",600,500);
//    imshow("src",src);
    imshow("src",src);

//    mat.zeros()

    cvtColor(src,mat,COLOR_BGR2GRAY);
    imshow("mat",mat);

    namedWindow("threshold",1);

    g_nTrackbarValue = 20;

    createTrackbar("yz", "threshold", &g_nTrackbarValue, g_nTrackbarMaxValue, on_Trackbar);
    on_Trackbar(g_nTrackbarValue, 0);//结果在回调函数中显示
    waitKey(0);

    return 0;
}

void on_Trackbar(int ,void*)
{
    threshold(mat,mat,g_nTrackbarValue,255,CV_THRESH_BINARY);
    imshow("threshold",mat);
}
