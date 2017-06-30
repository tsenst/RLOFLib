/** 
 * \file mainpage.h
 * \brief Documentation.
 * Documentation file.
 * \date 30.06.2017
 * \author Tobias Senst
 * \version 1.3
 */
/*!
 \mainpage Introduction
 This documentation contains a description of the RLOF library (available at http://www.nue.tu-berlin.de/menue/forschung/projekte/rlof/).
 
 The RLOF library contains:
 
  - compiled versions of PLK/RLOF based methods described in <a href="index.html#Senst2014">Senst et al. 2011/12/1314</a> (\b /RLOF/lib/).
  - sample CMake project ( \b /RLOFApp/ ).
  - <a href="http://de.mathworks.com/help/matlab/ref/mex.html" target="_blank">Matlab MEX-functions</a> and a Matlab sample script ( \b /Matlab/ ).
  - a detailed documentation ( \b /Doc/ ).
  
  RLOF library supports the following methods published in articles :
  
  - Robust local optical flow by shrinked Hampel norm, <a href="index.html#Senst2011">Senst et al. 2011</a>, <a href="index.html#Senst2012">Senst et al. 2012</a>.
  - Residual based support region construction for RLOF, <a href="index.html#Senst2011">Senst et al. 2011</a>, <a href="index.html#Senst2012">Senst et al. 2012</a>.
  - Cross based support region construction for PLK and RLOF, <a href="index.html#Senst2014">Senst et al. 2014</a>.
  - Iterative refinement strategy for PLK and RLOF using bilinear equations, <a href="index.html#Senst2013">Senst et al. 2013</a>.
  - Illumination robust model and global motion prior for PLK and RLOF, <a href="index.html#Senst2016">Senst et al. 2016</a>. 
  - To enable PLK implementations instead of the RLOF implementations please set rlof::Parameter::m_HampelNormS0 = std::numeric_limits<float>::max().
  
  The RLOFlib library is a sparse optical flow and feature tracking library. In this documentation we will use the definition of feature tracking. We use feature tracking 
  in the following context. For a given set of point (feature points) defined at positions in an image at a time t, the Feature tracking method is able to track the positions 
  of the feature points in the subsequent image at time t+1. In other words for each point of the feature set at time t the PLK and RLOF derived methods compute the motion at 
  these positions from image at time t to the subsequent image at time t+1.

  In order to increase the robustness of the proposed implementation and avoid dependencies we decided to no longer provide a GPU implementation. Instead we focus on CPU based 
  parallelization techniques such as the Streaming SIMD Extension instruction set (<a href="http://msdn.microsoft.com/de-de/library/y0dh78ez%28v=vs.90%29.aspx" target="_blank">SSE</a>) 
  and multi-threading with <a href="http://openmp.org/wp/openmp-specifications/" target="_blank">OpenMP</a>. The RLOF library C++ is compiled as a shared library and provides matlab MEX 
  wrapper functions. It supports Windows and Linux. 
  
  Read Section \ref Sample to learn more how to use and install the library.
 To build an application using the RLOF library please consider the \ref ToU and read the \ref Requirements.
 
 \section Matlab Matlab Mex-Function
  The Matlab package contains Mex-functions for each OS. 
  Call "help mex_SparseRLOF" or "help mex_DenseRLOF" for a description of the arguments and see "sampleRLOF.m" for an example use of the function.  
 
 \section Requirements Requirements
 Their should be no additional requirements to your OS. The library was tested with:
  
   - OpenCV3.1.0
   - Microsoft Visual Studio 2010 / 2012
   - Matlab 
   - Windows 7 (x64) / Linux (x64)
  
 The library was build using OpenCV 3.1.0. To enable the compatibility to another OpenCV version we provide the rlof::Image Wrapper interface.
 Therefore \b disable the linking of OpenCV using the USE_NO_OPENCV preprocessor flag.
 
 \section Change Change Log
 08/01/2013 Release Version 1.1
 - The runtime performance of the CPU implementation is improved by using Intel's Threading Building Blocks (Intel TBB) and Streaming SIMD Extensions SSE.
 
 17/11/2014 Release Version 1.2
 - Add Cross based and Bilinear equation based variations of PLK/RLOF.
 - Remove GPU support
 
 30/06/2017 Release Version 1.3
 - Add global motion prior allowing to improve the accuracy of estimation long-range motions
 - Add illumination robust model to imporve the accuracy in environments with illumination changes.
 - Intel's Threading Building Blocks (Intel TBB) is no longer supported. Parallelization will be based on SSE and OpenMP.
 
 \section Sample Sample
 The folder RLOFApp contains the RLOFApp.cpp file which demonstrates the usage of the RLOF library.
 
 The sample project can be build with cmake (from Version 2.7). Please set the following options:
	LIBRLOF_INCLUDE -> directing to the include directory containing the files RLOF_Flow.h and RLOF_Parameter.h
	LIBRLOF_PATH 	-> directing to the lib directory containing libRLOF_X lib files
	OpenCV_DIR 		-> directing to your local opencv directory.
  
 To run the sample please mention to announce the binary path "/lib/" e.g. by setting the environment PATH variable
 (e.g. PATH=D:/workspace/Arbeit_Senst/publicProjects/RLOFLib/lib/ ) in your project debugging settings.

 \section Contact Contact
 Tobias Senst: <senst@nue.tu-berlin.de> 
 
 \section ToU Terms of Use
 \subsection Copyright Copyright
 This file is the property of the author Tobias Senst and Communication Systems Group, 
 Technische Universitaet Berlin. All rights reserved. It may not be publicly 
 disclosed, distributed, used, copied or modified without prior written 
 authorization by a representative of Communication Systems Group, Technische 
 Universitaet Berlin or the author. Any modified version of this document needs to contain this header.        
 
 \subsection NonCommercial Personal, Non-Commercial or Academic Usage 
 You are free to use this software for whatever you like for non-commercial personal, non-commercial or academic usage. If you use this algorithm for a 
 scientific publication, please cite one of the following paper:

 \htmlonly
 <a name="Senst2016">
 @INPROCEEDINGS{Senst2016,</br>
 &nbsp; AUTHOR = {Tobias Senst and Jonas Geistert and Thomas Sikora},</br>
 &nbsp; TITLE = {Robust local optical flow: Long-range motions and varying illuminations},</br>
 &nbsp; BOOKTITLE = {IEEE International Conference on Image Processing},</br>
 &nbsp; YEAR = {2016},</br>
 &nbsp; PAGES = {4478--4482},</br>
 &nbsp; ADDRESS = {Phoenix, AZ, USA},</br>
 &nbsp; DOI:10.1109/ICIP.2016.7533207},</br>
 }</br>
 </a>	
  <a name="Senst2014">
 @INPROCEEDINGS{Senst2014, </br>
 &nbsp; AUTHOR = {Tobias Senst and Thilo Borgmann and Ivo Keller and Thomas Sikora},</br>
 &nbsp; TITLE = {Cross based Robust Local Optical Flow},</br>
 &nbsp; BOOKTITLE = {21th IEEE International Conference on Image Processing},</br>
 &nbsp; YEAR = {2014},</br>
 &nbsp; month = {okt},</br>
 &nbsp; pages = {1967--1971},</br>
 &nbsp; address = {Paris, France}, </br>
 &nbsp; doi = {}</br>
 } 
 </br>
 </a>
 <a name="Senst2013">
 @INPROCEEDINGS{Senst2013, </br>
 &nbsp; AUTHOR = {Tobias Senst and Jonas Geistert and Ivo Keller and Thomas Sikora},</br>
 &nbsp; TITLE = {Robust Local Optical Flow Estimation using Bilinear Equations for Sparse Motion Estimation},</br>
 &nbsp; BOOKTITLE = {20th IEEE International Conference on Image Processing},</br>
 &nbsp; YEAR = {2013},</br>
 &nbsp; month = {sep},</br>
 &nbsp; pages = {2499--2503},</br>
 &nbsp; address = {Melbourne, Australia}, </br>
 &nbsp; doi = {10.1109/ICIP.2013.6738515}</br>
 } 
 </br>
 </a>
 <a name="Senst2012">
 @ARTICLE{Senst2012, </br>
 &nbsp; AUTHOR = {Tobias Senst and Volker Eiselein and Thomas Sikora},</br>
 &nbsp; TITLE = {Robust Local Optical Flow for Feature Tracking},</br>
 &nbsp; JOURNAL = {IEEE Transactions on Circuits and Systems for Video Technology},</br>
 &nbsp; YEAR = {2012},</br>
 &nbsp; month={sep},</br>
 &nbsp; volume={22},</br>
 &nbsp; number={9},</br>
 &nbsp; pages={1377--1387},</br>
 &nbsp; doi={10.1109/TCSVT.2012.2202070}</br>
 }
 </br>
 </a>
 <a name="Senst2011">
 @INPROCEEDINGS{Senst2011,</br>
  &nbsp; AUTHOR = {Tobias Senst and Volker Eiselein and Ruben Heras Evangelio and  Thomas Sikora}</br>
  &nbsp; TITLE = {Robust Modified L2 Local Optical Flow Estimation and Feature Tracking},</br>
  &nbsp; BOOKTITLE = {IEEE Workshop on Motion and Video Computing},</br>
  &nbsp; YEAR = {2011},</br>
  &nbsp; MONTH = jan,</br>
  &nbsp; EDITOR = {Eric Mortensen},</br>
  &nbsp; PAGES = {685--690},</br>
  &nbsp; ADDRESS = {Kona, USA},</br>
  &nbsp; DOI = {10.1109/WACV.2011.5711571},</br>
 }
 </a>
\endhtmlonly

 \subsection commercialuse Commercial Usage
 It is not allowed to use any content of this package for any commercial
 use or any advertisement for upcoming commercial products. If you want to
 use any content for such a purpose please contact:
 Dipl.-Ing. Tobias Senst <senst@nue.tu-berlin.de>
 Prof. Dr.-Ing. Thomas Sikora <sikora@nue.tu-berlin.de>.
 
 \subsection warranties Warranties
 Software provided by Technische Universitaet Berlin with this document is
 provided "AS IS" and any express of implied warranties including, but
 not limited to, the implied warranties of merchantability and fitness
 for a particular purpose are disclaimed.
 In no event shall the author or contributors be liable for any direct,
 indirect, incidental, special, exemplary, or consequential damages
 (including, but not limited to, procurement of substitute goods or
 services, loss of use, data, or profits or business interruption) caused in
 any way out of the use of this software, even if advised of the possibility
 of such damage. 
 */