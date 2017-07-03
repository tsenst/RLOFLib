/** 
 * /file RLOFApp.cpp
 * /brief RLOF Example application.
 * /date 30.06.2017
 * /author Tobias Senst
 */

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <RLOF_Flow.h>


int main(int argc, char** argv)
{
	std::string filename1, filename2;
	if( argc < 2)
	{
		filename1 = "D:/Workspace/Senst/GIT/RLOFLib/Doc/ErnstReuter1.png";
		filename2 = "D:/Workspace/Senst/GIT/RLOFLib/Doc/ErnstReuter2.png";
	}
	else
	{
		filename1 = std::string(argv[1]);
		filename2 = std::string(argv[2]);
	}
	cv::Mat prevImg = cv::imread(filename1);
	if ( prevImg.empty())
	{
		std::cout<< "[ERROR] Unable to load " << filename1 << std::endl;
	}
	cv::Mat currImg = cv::imread(filename2);
	if ( currImg.empty())
	{
		std::cout<< "[ERROR] Unable to load " << filename2 << std::endl;
	}
	rlof::Image img0, img1;
	std::vector<rlof::CRPoint> prevPoints, currPoints;
	img0.attach(prevImg);
	img1.attach(currImg);

	// Setup parameter and initialize sparse RLOF
	rlof::Parameter rlof_Parmeter;
	rlof::SparseFlow * proc = rlof::SparseFlow::create(rlof_Parmeter);
	// Initialize flow field
	for(int r = 0; r < prevImg.rows; r++)
	{
		for(int c = 0; c < prevImg.cols; c++)
		{
			prevPoints.push_back(rlof::CRPoint(c,r));
		}
	}

	// run RLOF
	double time = static_cast<double>(cv::getTickCount());
	try
	{
	  proc->run(img0, img1, prevPoints, currPoints);
	}
	catch(std::runtime_error & e)
	{
	  std::cout << e.what() << std::endl;
	  return 1;
	}
	std::cout << " Runtime = " << (static_cast<double>(cv::getTickCount()) - time) / (cvGetTickFrequency() * 1000.f) << std::endl;
	
	// draw a rough idea of the dense flow field 
	cv::Mat flowU(prevImg.rows, prevImg.cols, CV_32FC1);
	cv::Mat flowV(prevImg.rows, prevImg.cols, CV_32FC1);
	cv::Mat flowHSV, flowRGB;
	std::vector<cv::Mat> flowVec(3);

	for( unsigned int n = 0 ; n < currPoints.size(); n++)
	{
		cv::Point pos(prevPoints[n].x, prevPoints[n].y);
		flowU.at<float>(pos) = currPoints[n].x - prevPoints[n].x;
		flowV.at<float>(pos) = currPoints[n].y - prevPoints[n].y;
	}
	
	cv::cartToPolar(flowU, flowV, flowVec[1], flowVec[0], true);
	flowVec[2] = cv::Mat::ones(flowVec[0].size(), flowVec[0].type()) * 255;
	cv::merge(flowVec, flowHSV);
	cv::cvtColor(flowHSV, flowRGB, cv::COLOR_HSV2BGR);
	flowRGB.convertTo(flowRGB, CV_8UC3);
	cv::imwrite("Flow.png", flowRGB);
	system("pause");
	return 0;
}

