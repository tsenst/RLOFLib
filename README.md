# ATTENTION !! THIS REPO IS STILL UNDER CONSTRUCTION PLEASE COME BACK IN A FEW DAYS
# Robust Local Optical Flow V1.3
This repository contains the RLOF library for Robust Local Optical Flow based motion estimation. The software implements several versions of the RLOF algorithm.
Please visit our webpage for more information (http://www.nue.tu-berlin.de/menue/forschung/projekte/rlof/).

	If you use this algorithm for a scientific publication, please cite the one of the paper listed below.

The RLOFlib library is a sparse optical flow and feature tracking library. The main objective of this library is to provide a **fast** and **accurate** motion estimation solution.
The main advantage of the RLOF approach is the adjustable runtime and computational complexity which is in contrast to most common optical flow methods linearly dependend on the number of motion vectors (features) to be estimated.
Thus the RLOF is a local optical flow method and most related to the PLK method ( better known as KLT Tracker ) and thus the famous Lucas Kanade method. 

We hope this software is useful to you. If you have any questions, comments, or issues, please do not hesitate to contact us.

	Tobias Senst: <senst AT nue.tu-berlin.de> 


## Requirements
Their should be no additional requirements to your OS. The library was tested with:
  - OpenCV3.1.0
  - Microsoft Visual Studio 2013 / 2017
  - Matlab 2015a
  - Windows 7 (x64) / xubuntu Linux (x64)
  
The library was build using OpenCV 3.1.0. To enable the compatibility to another OpenCV version we provide the rlof::Image Wrapper interface.
Therefore disable the linking of OpenCV using the USE_NO_OPENCV preprocessor flag.

## Installation 

```
git clone http://github.com/tsenst/RLOFLib
```
### C++ Interface 

The header of the C++ interface can be found in the `/include/` directory. The library files are located at the `/lib/` directory.
The library was build using OpenCV 3.1.0. To enable the compatibility to another OpenCV version we provide the rlof::Image Wrapper interface.
If no OpenCV will be used please set the USE_NO_OPENCV preprocessor flag to disable the OpenCV related code.
The C++ library files have been compiled with the following OS and development environments:
  - Visual Studio 2012 (vc120) / x64 / Windows 7 
  - Visual Studio 2017 (vc141) / x64 / Windows 7 
  - MinGW / x64 / Windows 7
  - gcc-5.4.0 / x64 / Ubuntu 17.04 ( in process )

An example applicatio nwhich will demonstrate the application of the RLOF library can be found in the directory `/RLOFApp/`.
More detailed description can be found [here...](https://github.com/tsenst/RLOFLib/tree/master/RLOFSample)

### Matlab Interface
The Matlab Mex-Files for each OS and are located at the `/Matlab/` directory.
The mex files have been compiled with the following OS and development environments:
  - Matlab 2015 / Visual Studio 2012 / x64 / Windows
  - Linux (... in progress)

Call `help mex_SparseRLOF` or `help mex_DenseRLOF` for a description of the arguments and see **RLOFSample.m** for an example use of the function.  
More detailed description can be found [here...](https://github.com/tsenst/RLOFLib/tree/master/Matlab)

### Python Interface 
The Python interface depends on *boost-python* and the python *numpy* package. The interface is located at the directory `\Python`.
In addition the example application depends on the *python-opencv* package.
#### Python 2.X
Install python, numpy and opencv packages.
```
sudo apt install python-numpy libboost-python-dev python-opencv
```
Run example application.
```
cd RLOFLib/Python
python RLOFExample.py
```
#### Python 3.X
Install python, numpy and pip3 packages. Use pip3 to install the python3 opencv package.
```
sudo apt install python3-numpy pip3 libboost-python-dev
sudo pip3 install opencv-python
```
Run example application.
```
cd RLOFLib/Python
python3 RLOFExample.py
```

The Python interface libraries have compiled with the following OS and development environments:
  - Python 3.5.2 / gcc-5.4.0 / Ubuntu 17.04 
  - Python 2.7.12 / gcc-5.4.0 / Ubuntu 17.04 
  - Python 3.5 / Visual Studio 2017 (vc141) / Windows 
	
Call `import rlof` to import the RLOF library. The **RLOFSample.py** shows how to use the RLOF library.
More detailed description can be found [here...](https://github.com/tsenst/RLOFLib/tree/master/Python)
	
## Description 
The RLOF library contains:
 
  - compiled versions of PLK/RLOF based methods described below (Senst et al. 2011-2016).
  - C++ interface and a sample project.
  - Matlab MEX-functions interface and a Matlab sample script.
  - supports Windows and Linux OS.
  - documentation.
  
   
RLOF library supports the following methods published in articles :
  
  - Robust local optical flow by shrinked Hampel norm, <a href="http://elvera.nue.tu-berlin.de/files/1277Senst2011.pdf">Senst et al. 2011</a>, <a href="http://elvera.nue.tu-berlin.de/files/1349Senst2012.pdf">Senst et al. 2012</a> .
  - Residual based support region construction for RLOF, <a href="http://elvera.nue.tu-berlin.de/files/1277Senst2011.pdf">Senst et al. 2011</a>, <a href="http://elvera.nue.tu-berlin.de/files/1349Senst2012.pdf">Senst et al. 2012</a>.
  
  		@ARTICLE{Senst2012,
		 AUTHOR = {Tobias Senst and Volker Eiselein and Thomas Sikora},
		 TITLE = {Robust Local Optical Flow for Feature Tracking},
		 JOURNAL = {IEEE Transactions on Circuits and Systems for Video Technology},
		 YEAR = {2012},                                                             
		 PAGES = {1377--1387},                                                      
		 DOI = {10.1109/TCSVT.2012.2202070}                                         
		} 
				
  - Cross based support region construction for PLK and RLOF, <a href="http://elvera.nue.tu-berlin.de/files/1448Senst2014.pdf">Senst et al. 2014</a>.
  
  		@INPROCEEDINGS{Senst2014,		    									
		 AUTHOR = {Tobias Senst and Thilo Borgmann and Ivo Keller and Thomas Sikora},
		 TITLE = {Cross based Robust Local Optical Flow},							
		 BOOKTITLE = {21th IEEE International Conference on Image Processing},      
		 YEAR = {2014},															    	 PAGES = {1967--1971},													    		}		 
		 
  - Iterative refinement strategy for PLK and RLOF using bilinear equations, <a href="http://elvera.nue.tu-berlin.de/files/1422Senst2013.pdf">Senst et al. 2013</a>.
  
 		@INPROCEEDINGS{Senst2013,	   
		 AUTHOR = {Tobias Senst and Jonas Geistert and Ivo Keller and Thomas Sikora},	
		 TITLE = {Robust Local Optical Flow Estimation using Bilinear Equations for Sparse Motion Estimation},	
		 BOOKTITLE = {20th IEEE International Conference on Image Processing},	   
		 YEAR = {2013},													    
		 PAGES = {2499--2503},
		 DOI = {10.1109/ICIP.2013.6738515},	
		}	
		
  - Illumination robust model and global motion prior for PLK and RLOF, <a href="http://elvera.nue.tu-berlin.de/files/1496Senst2016.pdf">Senst et al. 2016</a>.
  
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
parallelization techniques such as the Streaming SIMD Extension instruction set and multi-threading with OpenMP. 
  

