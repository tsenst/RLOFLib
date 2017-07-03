% mex function for computing local optical flow tracking
%
% Usage:
%
% [U, V] = mex_DenseRLOF(image1,image2);
% [U, V] = mex_DenseRLOF(image1,image2, parameter);
%
% The function estimates a dense optical flow field using the RLOF Alg-
% orithm which are described in the publications listes below.
%
% Arguments "image1" and "image2" are rgb images (3-dimensional arrays). 
% They are required to have the same dimension and they must be doubles. 
%
%
% The results "U" and "V" are the x- and y-components of the flow field.
%
% Argument "parameter" is the tuning parameter (struct). 
% Possible struct fields are:
%
%       "maxLevel"       					(5)     			A positive number specifying the number of levels used for the Gaussian pyramid.
%       "maxIter"    	 					(30)    			A positive number specifying the maximal number of iteration used for the iterative refinement.
%       "HampelNormS0"   					(3.2)     			A positive number specifying the shrinked Hampel norm parameter sigma_1 refering to Senst et al. 2012.
%       "HampelNormS1"    					(7)      			A positive number specifying the shrinked Hampel norm parameter sigma_2 refering to Senst et al. 2012.
%       "SmallWinSize"   					(9)     			A positive number specifying the minimal support region size (ignored if SR_FIXED is used)
%       "LargeWinSize"  					(21)     			A positive number specifying the maximal support region size (or the region size if SR_FIXED is used)
%       "MinEigenvalue"    					(0.0001f)       	A positive number specifying the minimal eigenvalue of the gradient matrix need to perform tracking.
%       "RansacReprojThresholdPercentil"    (10)      			A positive number from 1 to 99 specifying RANSAC inlier threshold refering to Senst et al. 2016 (ignored of no global motion prior is used) 
%       "SegmentationThreshold"    			(30)      			A positive number specifying the segmentation threshold &tau; as described in Senst et al. 2014.
%       "useIlluminationModel"    			(1)      			Enables the robust illumination model to improve the accuracy for environments with varying illuminations, introduced in Senst et al. 2016.
%       "useGlobalMotionPrior"    			(1)     			Enables the global motion prior to improve the accuracy for long-range motions, introduced in Senst et al. 2016.
%       "SupportRegionType"    				(SR_CROSS)      	Specifying the adaptive support region strategy to be used:
%																	- SR_FIXED  	Rectangle constant support region.
%        															- SR_CROSS  	Adaptive support region based on the cross-based segmentation introduced in Senst et al. 2016.
%       															- SR_RESIDUAL   Adaptive support region based on evaluatin the residual introduced in Senst et al. , Senst et al. 2012.
%       "SolverType"    					(ST_BILINEAR)       Specifying the iterative refinement strategy.
%        															- ST_STANDART 	Standard iterative inverse compositional solver.
%																	- ST_BILINEAR 	Bilinear equation solver, described in Senst et al. 2013.
%       "options"    						(PrintParameter)    Set to print the parameter struct to stdout.
% Tobias Senst
% TU-Berlin
% 30 Jun, 2017
%
%/******************************************************************************
% * COPYRIGHT:                                                                 * 
% *                                                                            *
% * This file is the property of the author Tobias Senst and Communication     *
% * Systems Group, Technische Universität Berlin. All rights reserved.         *
% *                                                                            *
% * It may not be publicly disclosed, distributed, used, copied or modified    *
% * without prior written authorization by a representative of                 *
% * Communication Systems Group, Technische Universität Berlin or the author.  *
% * Any modified version of this document needs to contain this header.        *
% ******************************************************************************/
%
%/******************************************************************************
%  * THERMS IF USAGE:                                                           *
%  * PERSONAL, NON-COMMERCIAL or ACADEMIC USAGE:                                *
%  *   You are free to use this software for whatever you like. If you use this *
%  *   algorithm for a scientific publication, please cite the one of the       *
%  *   following paper:                                                         *
%  *																			*
%  * @INPROCEEDINGS{Senst2016,			    								    *
%  *	AUTHOR = {Tobias Senst and Jonas Geistert and Thomas Sikora},			*
%  *	TITLE = {Robust local optical flow: Long-range motions and varying 		*
%  *  illuminations},															*
%  *	BOOKTITLE = {IEEE International Conference on Image Processing},		*
%  *	YEAR = {2016},															*
%  *	PUBLISHER = {IEEE},														*
%  *	PAGES = {4478--4482},													*
%  *	ADDRESS = {Phoenix, AZ, USA},											*
%  *  DOI:10.1109/ICIP.2016.7533207},											*
%  *  }																		    *
%  *																			*
%  * @INPROCEEDINGS{Senst2014,		    									    *
%  * AUTHOR = {Tobias Senst and Thilo Borgmann and Ivo Keller and Thomas		*
%  * Sikora},																	*
%  * TITLE = {Cross based Robust Local Optical Flow},							*
%  * BOOKTITLE = {21th IEEE International Conference on Image Processing},      *
%  * YEAR = {2014},															    *
%  * MONTH = okt,																*
%  * PAGES = {1967--1971},													    *
%  * ADDRESS = {Paris, France},												    *
%  * }																		    *
%  *																			*
%  * @INPROCEEDINGS{Senst2013,	    										    *
%  * AUTHOR = {Tobias Senst and Jonas Geistert and Ivo Keller and Thomas		*
%  * Sikora},																	*
%  * TITLE = {Robust Local Optical Flow Estimation using Bilinear Equations for *
%  * Sparse Motion Estimation},												    *
%  * BOOKTITLE = {20th IEEE International Conference on Image Processing},	    *
%  * YEAR = {2013},															    *
%  * MONTH = sep,																*
%  * PAGES = {2499--2503},													    *
%  * ADDRESS = {Melbourne, Australia},										    *
%  * DOI = {10.1109/ICIP.2013.6738515},										    *
%  * }																		    *
%  *                                                                            *
%  * @ARTICLE{Senst2012,                                                        *
%  * AUTHOR = {Tobias Senst and Volker Eiselein and Thomas Sikora},             *
%  * TITLE = {Robust Local Optical Flow for Feature Tracking},                  *
%  * JOURNAL = {IEEE Transactions on Circuits and Systems for Video Technology},*
%  * YEAR = {2012},                                                             *
%  * MONTH = sep,                                                               *
%  * PAGES = {1377--1387},                                                      *
%  * VOLUME = {22},                                                             *
%  * NUMBER = {9},                                                              *
%  * DOI = {10.1109/TCSVT.2012.2202070}                                         *
%  * }                                                                          *
%  *                                                                            *
%  * @INPROCEEDINGS{Senst2011,               	                                *
%  * AUTHOR = {Tobias Senst and Volker Eiselein and Rubén Heras Evangelio and   *
%  * Thomas Sikora},                                                            *
%  * TITLE = {Robust Modified L2 Local Optical Flow Estimation and Feature      *
%  * Tracking},                                                                 *
%  * BOOKTITLE = {IEEE Workshop on Motion and Video Computing},                 *
%  * YEAR = {2011},                                                             *
%  * MONTH = jan,                                                               *
%  * EDITOR = {Eric Mortensen},                                                 *
%  * PAGES = {685--690},                                                        *
%  * ADDRESS = {Kona, USA},                                                     *
%  * DOI = {10.1109/WACV.2011.5711571},                                         *
%  * }                                                                          *
%  ******************************************************************************/
%
%/******************************************************************************
% * WARRANTIES:                                                                *
% *                                                                            *
% * Software provided by Technische Universität Berlin with this document is   *
% * provided "AS IS" and any express of implied warranties including, but      *
% * not limited to, the implied warranties of merchantability and fitness      *
% * for a particular purpose are disclaimed.                                   *
% * In no event shall the author or contributors be liable for any direct,     *
% * indirect, incidental, special, exemplary, or consequential damages         *
% * (including, but not limited to, procurement of substitute goods or         *
% * services, loss of use, data, or profits or business interruption) caused in*
% * any way out of the use of this software, even if advised of the possibility*
% * of such damage.                                                            *
% ******************************************************************************/