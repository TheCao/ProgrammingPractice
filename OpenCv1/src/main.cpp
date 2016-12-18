#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    const string file_name = "sunflower.jpg";
    Mat img = imread(file_name);
    if( !img.data )
    {
        cout << "Nie odnalezionu pliku " << file_name;
        return -1;
    }
    const string window_name = "OpenCV_1";
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);
    imshow(window_name, img);
    waitKey(0);
    return 0;
}
