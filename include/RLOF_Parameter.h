/** 
 * \file RLOF_Parameter.h
 * \brief RLOF Parameter.
 * \date 30.06.2017
 * \author Tobias Senst
 */
 
/******************************************************************************
 * THERMS IF USAGE:                                                           *
 * PERSONAL, NON-COMMERCIAL or ACADEMIC USAGE:                                *
 *   You are free to use this software for whatever you like. If you use this *
 *   algorithm for a scientific publication, please cite the one of the       *
 *   following paper:                                                         *
 *																			  *
 * @INPROCEEDINGS{Senst2016,			    								  *
 *	AUTHOR = {Tobias Senst and Jonas Geistert and Thomas Sikora},			  *
 *	TITLE = {Robust local optical flow: Long-range motions and varying 		  *
 *  illuminations},															  *
 *	BOOKTITLE = {IEEE International Conference on Image Processing},		  *
 *	YEAR = {2016},															  *
  *	PUBLISHER = {IEEE},														  *
 *	PAGES = {4478--4482},													  *
 *	ADDRESS = {Phoenix, AZ, USA},											  *
 *  DOI:10.1109/ICIP.2016.7533207},											  *
 *  }																		  *
 *																			  *
 * @INPROCEEDINGS{Senst2014,		    									  *
 * AUTHOR = {Tobias Senst and Thilo Borgmann and Ivo Keller and Thomas		  *
 * Sikora},																	  *
 * TITLE = {Cross based Robust Local Optical Flow},							  *
 * BOOKTITLE = {21th IEEE International Conference on Image Processing},	  *
 * YEAR = {2014},															  *
 * MONTH = okt,																  *
 * PAGES = {1967--1971},													  *
 * ADDRESS = {Paris, France},												  *
 * }																		  *
 *																			  *
 * @INPROCEEDINGS{Senst2013,	    										  *
 * AUTHOR = {Tobias Senst and Jonas Geistert and Ivo Keller and Thomas		  *
 * Sikora},																	  *
 * TITLE = {Robust Local Optical Flow Estimation using Bilinear Equations for *
 * Sparse Motion Estimation},												  *
 * BOOKTITLE = {20th IEEE International Conference on Image Processing},	  *
 * YEAR = {2013},															  *
 * MONTH = sep,																  *
 * PAGES = {2499--2503},													  *
 * ADDRESS = {Melbourne, Australia},										  *
 * DOI = {10.1109/ICIP.2013.6738515},										  *
 * }																		  *
 *                                                                            *
 * @ARTICLE{Senst2012,                                                        *
 * AUTHOR = {Tobias Senst and Volker Eiselein and Thomas Sikora},             *
 * TITLE = {Robust Local Optical Flow for Feature Tracking},                  *
 * JOURNAL = {IEEE Transactions on Circuits and Systems for Video Technology},*
 * YEAR = {2012},                                                             *
 * MONTH = sep,                                                               *
 * PAGES = {1377--1387},                                                      *
 * VOLUME = {22},                                                             *
 * NUMBER = {9},                                                              *
 * DOI = {10.1109/TCSVT.2012.2202070}                                         *
 * }                                                                          *
 *                                                                            *
 * @INPROCEEDINGS{Senst2011,               	                                  *
 * AUTHOR = {Tobias Senst and Volker Eiselein and Rubén Heras Evangelio and   *
 * Thomas Sikora},                                                            *
 * TITLE = {Robust Modified L2 Local Optical Flow Estimation and Feature      *
 * Tracking},                                                                 *
 * BOOKTITLE = {IEEE Workshop on Motion and Video Computing},                 *
 * YEAR = {2011},                                                             *
 * MONTH = jan,                                                               *
 * EDITOR = {Eric Mortensen},                                                 *
 * PAGES = {685--690},                                                        *
 * ADDRESS = {Kona, USA},                                                     *
 * DOI = {10.1109/WACV.2011.5711571},                                         *
 * }                                                                          *
 ******************************************************************************/
#ifndef RLOF_RLOFPARAMETER_H
#define RLOF_RLOFPARAMETER_H
namespace rlof
{
	/*! Enumeration specifying the adaptive support region strategy to be used.
	*/
    enum MSupportRegionType{
        SR_FIXED = 0,			/*!< Rectangle constant support region.*/
        SR_CROSS = 1,			/*!< Adaptive support region based on the cross-based segmentation introduced in <a href="index.html#Senst2016">Senst et al. 2016</a>.*/
        SR_RESIDUAL = 2,		/*!< Adaptive support region based on evaluatin the residual introduced in <a href="index.html#Senst2011">Senst et al. 2011</a>, <a href="index.html#Senst2012">Senst et al. 2012</a>.*/
    };
	
	/*! Enumeration specifying the iterative refinement strategy.
	*/
    enum MSolverType{
        ST_STANDART = 0,		 /*!< Standard iterative inverse compositional solver . */
        ST_BILINEAR = 1			 /*!< Bilinear equation solver, described in <a href="index.html#Senst2013">Senst et al. 2013</a> .*/
    };
	
	/*!\class Parameter
	*  \brief RLOF parameter class
	*  The class provides the variables to be set up for parameterizing the RLOF algorithm. 
	*  The different parameters are associated with variations of the RLOF algortihm descibed 
	*  in the publications listes above.
	*/
    class Parameter
    {
    public:
        Parameter()
                : m_SupportRegionType(SR_CROSS)
                , m_SolverType(ST_BILINEAR)
                , m_UseIlluminationModel(true)
                , m_UseGlobalMotionPrior(true)
                , m_MaxLevel(5)
                , m_MaxIter(30)
                , m_SmallWinSize(9)
                , m_LargeWinSize(21)
                , m_MinEigenvalue(0.0001f)
                , m_RansacReprojThresholdPercentil(10.f)
                , m_HampelNormS0(3.2f)
                , m_HampelNormS1(7.f)
                , m_SegmentationThreshold(25)
                {}
        MSupportRegionType	m_SupportRegionType;				/*!< Enumeration specifying support region construction.*/
        MSolverType	        m_SolverType;						/*!< Enumeration specifying iterative refinement strategy.*/
        bool                m_UseIlluminationModel;				/*!< Enables the robust illumination model to improve the accuracy for environments with varying illuminations, introduced in <a href="index.html#Senst2016">Senst et al. 2016</a> */
        bool                m_UseGlobalMotionPrior;				/*!< Enables the global motion prior to improve the accuracy for long-range motions, introduced in <a href="index.html#Senst2016">Senst et al. 2016</a> */
        int					m_MaxLevel;							/*!< A positive number specifying the number of levels used for the Gaussian pyramid.*/
        int					m_MaxIter;							/*!< A positive number specifying the maximal number of iteration used for the iterative refinement.*/
        int					m_SmallWinSize;						/*!< A positive number specifying the minimal support region size (ignored if SR_FIXED is used).*/
        int					m_LargeWinSize;						/*!< A positive number specifying the maximal support region size (or the region size if SR_FIXED is used).*/
        float				m_MinEigenvalue;					/*!< A positive number specifying the minimal eigenvalue of the gradient matrix need to perform tracking.*/
        float				m_RansacReprojThresholdPercentil;	/*!< A positive number from 1 to 99 specifying RANSAC inlier threshold refering to <a href="index.html#Senst2016">Senst et al. 2016</a> (ignored of no global motion prior is used) */
        float           	m_HampelNormS0;						/*!< A positive number specifying the shrinked Hampel norm parameter &sigma;<sub>1</sub> refering to <a href="index.html#Senst2012">Senst et al. 2012</a>.
																 * If m_HampelNormS0 = std::numeric_limits<float>::max() PLK will be applied instead of RLOF. */
        float           	m_HampelNormS1;						/*!< A positive number specifying the shrinked Hampel norm parameter &sigma;<sub>2</sub> refering to <a href="index.html#Senst2012">Senst et al. 2012</a>.*/
        int			        m_SegmentationThreshold;			/*!< A positive number specifying the segmentation threshold &tau; as described in <a href="index.html#Senst2014">Senst et al. 2014</a>.*/
    };

}

#endif //RLOF_RLOFPARAMETER_H
