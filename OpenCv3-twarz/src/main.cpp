#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;
CascadeClassifier face_cascade;
void detectFace(Mat img);

int main( int argc, char** argv )
{
    VideoCapture capture = VideoCapture(0); //Camera Handler
    string face_cascade_name = "haarcascade_frontalface_alt.xml";

    Mat frame,img;

    if( !face_cascade.load( face_cascade_name ) )
    {
        cout << "Nie znaleziono pliku " << face_cascade_name << ".";
        return -2;
    }
    while ( waitKey(20) != 27 )
    {
        capture >> frame;
        frame.copyTo(img);
        detectFace(img);

    }
    capture.release();
    return 0;
}

void detectFace(Mat img)
{
	static vector<Rect> faces;
	static Mat img_gray;

	cvtColor(img,img_gray, CV_BGR2GRAY);
	equalizeHist(img_gray, img_gray);
	face_cascade.detectMultiScale(img_gray, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50) );
	    for( unsigned i = 0; i < faces.size(); i++ )
	    {
	        Rect rect_face( faces[i] );    //Kwadrat okreslaj¹cy twarz
	       // ellipse( img, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 120, 12 ), 2, 2, 0 );
	        rectangle(img, rect_face, Scalar( 120, 5, 86 ), 2, 2, 0  );
	    }
	 imshow("Kamera",img);                      //Pokazanie obrazka w oknmie o nazwie "Hello Face !"

}
