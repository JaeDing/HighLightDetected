//#include <QtCore/QCoreApplication>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "iostream"

using namespace std;
using namespace cv;

//声明全局变量
//int g_nTrackbarValue;
//const int g_nTrackbarMaxValue = 255;     //滑动条最大值

//声明回掉函数
//void on_Trackbar(int val, void*);
void Morphology_Operations( int, void* );

Mat src,mat,dst,obj;

int morph_elem = 0;
int morph_size = 3;
int morph_operator = 1;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

char* window_name = "Morphology Transformations Demo";

int main()
{
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

    cvtColor(src,mat,COLOR_BGR2GRAY);
    imshow("mat",mat);

    int arr[256] = {0};
    for (size_t i=0; i<mat.total(); i++)
    {
        arr[mat.data[i]]++;
    }
    threshold(mat,dst,210,255,CV_THRESH_BINARY);
    /// 创建显示窗口
     namedWindow( window_name, CV_WINDOW_AUTOSIZE );

     /// 创建选择具体操作的 trackbar
     createTrackbar("Operator:\n 0: Opening - 1: Closing \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name, &morph_operator, max_operator, Morphology_Operations );

     /// 创建选择内核形状的 trackbar
     createTrackbar( "Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
                     &morph_elem, max_elem,
                     Morphology_Operations );

     /// 创建选择内核大小的 trackbar
     createTrackbar( "Kernel size:\n 2n +1", window_name,
                     &morph_size, max_kernel_size,
                     Morphology_Operations );

     /// 启动使用默认值
     Morphology_Operations( 0, 0 );
//    namedWindow("threshold",1);

//    g_nTrackbarValue = 200;

//    createTrackbar("yz", "threshold", &g_nTrackbarValue, g_nTrackbarMaxValue, on_Trackbar);
//    on_Trackbar(g_nTrackbarValue, 0);//结果在回调函数中显示
    waitKey(0);

    return 0;
}

//void on_Trackbar(int ,void*)
//{
//    cout << g_nTrackbarValue << endl;
//    threshold(mat,dst,g_nTrackbarValue,255,CV_THRESH_BINARY);
//    vector<std::vector<Point> > contours;
//    vector<Vec4i> hierarchy;
//    findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//    src.copyTo(obj);
//    for(int i = 0;i < contours.size(); i++)
//    {
//        drawContours(obj, contours, i, Scalar(0, 0, 255), 1, 8, hierarchy, 0, Point(0,0));//绘制轮廓

//    }
//    imshow("threshold",dst);
//    imshow("object",obj);
//}
void Morphology_Operations( int, void* )
{
  // 由于 MORPH_X的取值范围是: 2,3,4,5 和 6
  int operation = morph_operator + 2;

  Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

  /// 运行指定形态学操作
  morphologyEx( dst, obj, operation, element );
  vector<std::vector<Point> > contours;
  vector<Vec4i> hierarchy;
  findContours(obj, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//    blur(dst,dst,Size(3,3));//对输入的图像src进行均值滤波
//    fitEllipse(contours);
  for(int i = 0;i < contours.size(); i++)
  {
      drawContours(obj, contours, i, Scalar(255, 0, 0), CV_FILLED, 8, hierarchy, 0, Point(0,0));//绘制轮廓
  }
  imshow("obj",obj);

  imshow( window_name, obj );
  }
