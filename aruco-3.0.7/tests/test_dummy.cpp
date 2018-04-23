#include <iostream>
#include "aruco.h"
#include <opencv2/highgui.hpp>
int main(int argc,char **argv)
{
   try
   {
       if (argc!=2) throw std::runtime_error("Usage: inimage");
       aruco::MarkerDetector MDetector;
       //read the input image
       cv::Mat InImage=cv::imread(argv[1]);
     //Ok, let's detect
       MDetector.setDictionary("ARUCO_MIP_36h12");
       auto Markers=MDetector.detect(InImage);
       //for each marker, draw info and its boundaries in the image
       for(auto m:MDetector.detect(InImage)){
           std::cout<<m<<std::endl;
           m.draw(InImage);
       }
       cv::imshow("in",InImage);
       cv::waitKey(0);//wait for key to be pressed
   } catch (std::exception &ex)
   {
       std::cout<<"Exception :"<<ex.what()<<std::endl;
   }
}
