This repo is under construction. Please come back in a few days.
Thank You 
Tobias Senst

# Robust Local Optical Flow V1.3
This repository contains a description of the RLOF library on Robust Local Optical Flow estimation. Please visit our webpage for more information (http://www.nue.tu-berlin.de/menue/forschung/projekte/rlof/).
The RLOFlib library is a sparse optical flow and feature tracking library. In this documentation we will use the definition of feature tracking. We use feature tracking in the following context. 
For a given set of point (feature points) defined at positions in an image at a time t, the Feature tracking method is able to track the positions of the feature points in the subsequent image at time t+1. 
In other words for each point of the feature set at time t the PLK and RLOF derived methods compute the motion at these positions from image at time t to the subsequent image at time t+1.

The RLOF library contains:
 
  - compiled versions of PLK/RLOF based methods described in Senst et al. 2011-2016.
  - sample CMake project.
  - Matlab MEX-functions interface and a Matlab sample script.
  - documentation.
  
RLOF library supports the following methods published in articles :
  
  - Robust local optical flow by shrinked Hampel norm, Senst et al. 2011, Senst et al. 2012.
  - Residual based support region construction for RLOF, Senst et al. 2011, Senst et al. 2012.
  
  		@ARTICLE{Senst2012,
		 AUTHOR = {Tobias Senst and Volker Eiselein and Thomas Sikora},
		 TITLE = {Robust Local Optical Flow for Feature Tracking},
		 JOURNAL = {IEEE Transactions on Circuits and Systems for Video Technology},
		 YEAR = {2012},                                                             
		 PAGES = {1377--1387},                                                      
		 DOI = {10.1109/TCSVT.2012.2202070}                                         
		} 
				
  - Cross based support region construction for PLK and RLOF, Senst et al. 2014.
  
  		@INPROCEEDINGS{Senst2014,		    									
		 AUTHOR = {Tobias Senst and Thilo Borgmann and Ivo Keller and Thomas Sikora},
		 TITLE = {Cross based Robust Local Optical Flow},							
		 BOOKTITLE = {21th IEEE International Conference on Image Processing},      
		 YEAR = {2014},															    	 PAGES = {1967--1971},													    		}		 
		 
  - Iterative refinement strategy for PLK and RLOF using bilinear equations, Senst et al. 2013.
  
 		@INPROCEEDINGS{Senst2013,	   
		 AUTHOR = {Tobias Senst and Jonas Geistert and Ivo Keller and Thomas Sikora},	
		 TITLE = {Robust Local Optical Flow Estimation using Bilinear Equations for Sparse Motion Estimation},	
		 BOOKTITLE = {20th IEEE International Conference on Image Processing},	   
		 YEAR = {2013},													    
		 PAGES = {2499--2503},
		 DOI = {10.1109/ICIP.2013.6738515},	
		}	
		
  - Illumination robust model and global motion prior for PLK and RLOF, <a href="index.html#Senst2016">Senst et al. 2016</a>.
  
		@INPROCEEDINGS{Senst2016,			    							
		 AUTHOR = {Tobias Senst and Jonas Geistert and Thomas Sikora},		
		 TITLE = {Robust local optical flow: Long-range motions and varying illuminations},				
		 BOOKTITLE = {IEEE International Conference on Image Processing},		
		 YEAR = {2016},			
		 PAGES = {4478--4482},													
		 DOI:10.1109/ICIP.2016.7533207},										
		}
		
  - To enable PLK implementations instead of the RLOF implementations please set rlof::Parameter::m_HampelNormS0 = std::numeric_limits<float>::max().
    
In order to increase the robustness of the proposed implementation and avoid dependencies we decided to no longer provide a GPU implementation. Instead we focus on CPU based 
parallelization techniques such as the Streaming SIMD Extension instruction set and multi-threading with OpenMP. The RLOF library C++ is compiled as a shared library and provides matlab MEX 
wrapper functions. It supports Windows and Linux. 
  
# Matlab Mex-Function
The Matlab package contains Mex-functions for each OS. 
Call "help mex_SparseRLOF" or "help mex_DenseRLOF" for a description of the arguments and see "RLOFSample.m" for an example use of the function.  
  
#Requirements
Their should be no additional requirements to your OS. The library was tested with:
  - OpenCV3.1.0
  - Microsoft Visual Studio 2010 / 2012
  - Matlab 2015a
  - Windows 7 (x64) / xubuntu Linux (x64)
The library was build using OpenCV 3.1.0. To enable the compatibility to another OpenCV version we provide the rlof::Image Wrapper interface.
Therefore disable the linking of OpenCV using the USE_NO_OPENCV preprocessor flag.

# Sample C++
The folder RLOFApp contains the RLOFApp.cpp file which demonstrates the usage of the RLOF library.
 
The sample project can be build with cmake (from Version 2.7). Please set the following options:
 - LIBRLOF_INCLUDE -> directing to the include directory containing the files RLOF_Flow.h and RLOF_Parameter.h
 - LIBRLOF_PATH 	-> directing to the lib directory containing libRLOF_X lib files
 - OpenCV_DIR 		-> directing to your local opencv directory.
  
To run the sample please mention to announce the binary path "/lib/" e.g. by setting the environment PATH variable
(e.g. PATH=D:/workspace/Arbeit_Senst/publicProjects/RLOFLib/lib/ ) in your project debugging settings.

# Contact 
If you have questions regarding the implementation please contact:
	Tobias Senst: <senst AT nue.tu-berlin.de> 
