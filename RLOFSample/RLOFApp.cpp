/** 
 * \file RLOFApp.cpp
 * \brief RLOF Example application.
 * \date 30.06.2017
 * \author Tobias Senst
 */

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <RLOF_Flow.h>


int main(int argc, char** argv)
{
	cv::Mat prevImg = cv::imread("../../Doc/ErnstReuter1.png");
	cv::Mat currImg = cv::imread("../../Doc/ErnstReuter2.png");
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
	double time = static_cast<double>(cvGetTickCount());
	try
	{
	  proc->run(img0, img1, prevPoints, currPoints);
	}
	catch(std::runtime_error & e)
	{
	  std::cout << e.what() << std::endl;
	  return 1;
	}
	time = static_cast<double>(cvGetTickCount()) / (cv::getTickFrequency() * 1000);
	std::cout << " Time = " << time << std::endl;
	
	// draw a rough idea of the dense flow field 
	cv::Mat flow(2 * prevImg.rows, prevImg.cols, CV_8UC1);
	cv::Mat flowU(flow, cv::Rect(0,0,prevImg.cols,prevImg.rows));
	cv::Mat flowV(flow, cv::Rect(0,prevImg.rows,prevImg.cols,prevImg.rows));

	for( unsigned int n = 0 ; n < currPoints.size(); n++)
	{
		cv::Point pos(prevPoints[n].x, prevPoints[n].y);
		flowU.at<uchar>(pos) = cv::saturate_cast<uchar>(currPoints[n].x - prevPoints[n].x + 128);
		flowV.at<uchar>(pos) = cv::saturate_cast<uchar>(currPoints[n].y - prevPoints[n].y + 128);
	}
	
	cv::imshow("Flow", flow);
	cv::waitKey(-1);
	return 0;
}

