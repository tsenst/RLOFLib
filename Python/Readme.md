# Example Application
This small sample project demonstrates the application of the RLOF interface for computing a dense optical flow field 
and sparse motion vectors. The demo loads two images, which can be passed by the input arguments or are the Ernstreuter 
images in the doc folder, computes the dense optical flow field and a grid of motion vectors and write the results as 
color coded image to Flow.png.

## RLOF parameter description
The RLOF parameter interface function **set_param** comes with the following parameters:
```
rlofProc = rlof.RLOFEstimator()
rlofProc.set_param(
  parameters["SolverType"],         
   # Specifying the iterative refinement strategy.
   # - "ST_STANDART" 	Standard iterative inverse compositional solver.
   # - "ST_BILINEAR" 	Bilinear equation solver, described in Senst et al. 2013.
  parameters["SupportRegionType"],  
   # Specifying the adaptive support region strategy to be used: 
   #  - "SR_FIXED"  	Rectangle constant support region.
   #  - "SR_CROSS"  	Adaptive support region based on the cross-based segmentation introduced in Senst et al. 2016.
   #  - "SR_RESIDUAL"   Adaptive support region based on evaluatin the residual introduced in Senst et al. , Senst et al. 2012.
  parameters["maxLevel"],           
   # A positive number specifying the number of levels used for the Gaussian pyramid.
  parameters["maxIter"],            
   # A positive number specifying the maximal number of iteration used for the iterative refinement.
  parameters["largeWinSize"], 
   # A positive number specifying the maximal support region size (or the region size if SR_FIXED is used).
  parameters["smallWinSize"],
   # A positive number specifying the minimal support region size (ignored if SR_FIXED is used).
  parameters["HampelNormS0"], 
   # A positive number specifying the shrinked Hampel norm parameter sigma_1 refering to Senst et al. 2012.
  parameters["HampelNormS1"],  
   # A positive number specifying the shrinked Hampel norm parameter sigma_2 refering to Senst et al. 2012.
  parameters["segmentationThreshold"], 
   # A positive number specifying the segmentation threshold &tau; as described in Senst et al. 2014.
  parameters["RansacReprojThresholdPercentil"], 
   # A positive number from 1 to 99 specifying RANSAC inlier threshold refering to Senst et al. 2016 (ignored of no global motion prior is used) 
  parameters["minEigenvalue"], 
   # A positive number specifying the minimal eigenvalue of the gradient matrix need to perform tracking.
  parameters["useIlluminationModel"], 
   # Enables the robust illumination model to improve the accuracy for environments with varying illuminations, introduced in Senst et al. 2016.
  parameters["useGlobalMotionPrior"]
   # Enables the global motion prior to improve the accuracy for long-range motions, introduced in Senst et al. 2016.
  )
```

The example application has been tested with the following OS configurations:
 - [x] Python 3.5.2 /  Ubuntu 17.04 
 - [x] Python 2.7.12 / Ubuntu 17.04 

