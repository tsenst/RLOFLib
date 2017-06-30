/** 
 * \file RLOF_Flow.h
 * \brief RLOF interface.
 * \date 30.06.2017
 * \author Tobias Senst
 */

#ifndef RLOF_RLOF_FLOW_H
#define RLOF_RLOF_FLOW_H

#ifndef DECL_RLOF_SPEC
	#ifdef WIN32
		#ifdef BUILDDLL
		     #define DECL_RLOF_SPEC __declspec(dllexport)
		#else
			 #define DECL_RLOF_SPEC __declspec(dllimport)
		#endif // DLL_EXPORT
    #else
        #define DECL_RLOF_SPEC
    #endif
#endif

//#define USE_NO_OPENCV   // set this flag if used without OpenCV

#ifndef USE_NO_OPENCV
#include <opencv2/core.hpp>
#endif
#include "RLOF_Parameter.h"
#include <vector>

namespace rlof
{
	/*!\class Image
	*  \brief RLOF Wrapper Class for BGR image data
	*/
	class Image
    {
    public:
		Image()
		 : m_DataPtr(NULL)
		 , m_Cols(0)
		 , m_Rows(0)
		 , m_Step(0)
		{}
	
        #ifndef USE_NO_OPENCV
		/*! Function copies cv::Mat header information and attaches data pointer.
		 *\param src BGR image to be attached.
		*/
        void attach(cv::Mat & src)
        {
			if (src.type() != CV_8UC3)
			throw(std::runtime_error("[ERROR] Wrong image type (CV_8UC3 needed)."));
            m_DataPtr = src.ptr<unsigned char>();
            m_Step = src.step;
            m_Rows = src.rows;
            m_Cols = src.cols;
            if( src.type() != CV_8UC3)
				throw(std::runtime_error("Image::attach ERROR image has to be of type CV_8UC3"));
        }
        #endif
        unsigned char * m_DataPtr;
        int     m_Step;
        int     m_Rows;
        int     m_Cols;
    };

	/*!\class CRPoint
	*  \brief RLOF Wrapper Class for Points
	*/
	class CRPoint
    {
    public:
        //! Default constructor
        CRPoint()
                : x(0)
                , y(0)
        {}
        /*! Constructor with initialisations.
        *\param _x Value of the x postion
        *\param _y Value of the y postion
        */
        CRPoint(const float _x, const float _y)
                : x(_x)
                , y(_y)
        {}
        float x,y;
    };

    /*!\class SparseFlow
	*  \brief RLOF Sparse Flow class
	*  This class implemets a private constructor. To initialize this class use the static create function.
	*/
    class DECL_RLOF_SPEC SparseFlow
    {
    public:
		/*! Destructor */
        ~SparseFlow();
		/*! Create SparseFlow object based on a predefined parameters
		 *\param param Parameter specifying the used RLOF method and parameters.
		*/
        static SparseFlow * create(Parameter param);
		//! Perform sparse optical flow estimation. 
		/*! Track a set of features points (prevPts) that are specified by a 2D point list and store the tracked positions at the (currPts) point list by using the image informations
		 * providen by the prevImage and currImage. If these images have to be bgr valued images (i.e. m_Step >= 3*m_Cols). 
		 *\param prevImage Wrapper object to an rgb image at time t. 
		 *\param currImage Wrapper object to an rgb image at time t+1. 
		 *\param prevPts Features tp track as point list at time t.
		 *\param currPts Tracked features as point list to time t+1.
		*/
        void run(const Image & prevImage, const Image & currImage, const std::vector<CRPoint> & prevPts, std::vector<CRPoint> & currPts);

    private:
		/*! Constructor */
		SparseFlow(){};
        void * m_InternalBuffer;
    };

};

#endif //RLOF_RLOF_FLOW_H
