#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <fstream>

using namespace cv;
using namespace std;

 int main( int argc, char** argv )
 {
  int type = 1;//img
  Mat imgOriginal;
  
  VideoCapture cap(argv[1]); // try capture the video
  if(argc >= 2)
  { 
      type = 2; //video

  }
  else
  {
    imgOriginal = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
  }
  
  int run = atoi(argv[2]);

  namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
  int iLowH,iHighH;
  int iLowS,iHighS;
  int iLowV,iHighV;

  fstream cfile;
  cfile.open("/home/nithin/.hsvConfig", std::fstream::in | std::fstream::out | std::fstream::app);
  if( cfile.peek() == std::ifstream::traits_type::eof() )
  {
   	cout<<"empty file"<<endl;
    iLowH = 0;
    iHighH = 179;

    iLowS = 0; 
    iHighS = 255;

    iLowV = 0;
    iHighV = 255;
  }
  else
  {
     cfile>>iLowH>>iHighH>>iLowS>>iHighS>>iLowV>>iHighV;
     cout<<"config read"<<endl;
  }
  cfile.close();
  
  //Create trackbars in "Control" window
  cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
  cvCreateTrackbar("HighH", "Control", &iHighH, 179);

  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
  cvCreateTrackbar("HighS", "Control", &iHighS, 255);

  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
  cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    int i =1;
    while (true)
    {
      
      int k = waitKey(30);
      //cout<<k<<endl;
      if (type == 2 && i == 1)
      {
        
        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            cfile.open("/home/nithin/.hsvConfig", std::fstream::out | std::fstream::trunc);
            cfile<<iLowH<<" "<<iHighH<<" "<<iLowS<<" "<<iHighS<<" "<<iLowV<<" "<<iHighV;
            cout<<"saved config . . ."<<endl;
            cfile.close();
            break;
        }
        i = 2;
      }

    Mat imgHSV;

   cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
 
  Mat imgThresholded;

   inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
  //morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

   //morphological closing (fill small holes in the foreground)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

   imshow("Thresholded Image", imgThresholded); //show the thresholded image
  imshow("Original", imgOriginal); //show the original image

  /*if (run == 1)
  {
    waitKey(0);
  }*/
        if ( k == 27|| k == 1048603 ) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
        cout << "esc key is pressed by user" << endl;
    
        cfile.open("/home/nithin/.hsvConfig", std::fstream::out | std::fstream::trunc);
   	    cfile<<iLowH<<" "<<iHighH<<" "<<iLowS<<" "<<iHighS<<" "<<iLowV<<" "<<iHighV;
        cout<<"saved config . . ."<<endl;
  	    cfile.close();
        break; 
      }
      else if ( k == 110 || k == 1048686 )
       {
            i=1;
       }
    }

   return 0;

}
