import numpy as np
import cv2
import rlof
import time 


# set rlof parameters
parameters = {  "SolverType" : "ST_BILINEAR",
                "SupportRegionType" : "SR_CROSS", 
                "maxLevel" : 9,
                "maxIter" : 30,
                "largeWinSize" : 21,
                "smallWinSize"  : 9,
                "HampelNormS0"  : 3.2,
                "HampelNormS1": 7.0 ,
				"segmentationThreshold": 25 ,
				"RansacReprojThresholdPercentil": 10.0 ,
				"minEigenvalue": 0.0001 ,
				"useIlluminationModel": True ,
				"useGlobalMotionPrior": False 
				} 
# load images 
prevImg = cv2.imread('../Doc/ErnstReuter1.png')
currImg = cv2.imread('../Doc/ErnstReuter2.png')

rlofProc = rlof.RLOFEstimator()
rlofProc.set_param(parameters["SolverType"], 
	parameters["SupportRegionType"],
	parameters["maxLevel"], parameters["maxIter"], 
	parameters["largeWinSize"], 
	parameters["smallWinSize"],
  parameters["HampelNormS0"], 
  parameters["HampelNormS1"],  
  parameters["segmentationThreshold"], 
  parameters["RansacReprojThresholdPercentil"], 
  parameters["minEigenvalue"], 
  parameters["useIlluminationModel"], 
  parameters["useGlobalMotionPrior"])

# prepare pointlist 
(h,w) = (prevImg.shape[0], prevImg.shape[1] )
a = np.meshgrid( np.arange(9,w,10) , np.arange(9,h,10))
prevPoints = np.vstack((a[0].ravel(), a[1].ravel() )).transpose().astype(np.float32).copy()				   
				
# sparse optical flow estimation e.g. to compute a grid of motion vectors
start = time.time();
currPoints = rlofProc.sparse_flow(prevImg, currImg, prevPoints)
end = time.time();
print( "\nSparse Optical Flow Estimation\n")
print( "#Features = " + str(prevPoints.shape[0]))
print( "Runtime[sec] = " + str(end - start ));

# draw sparse motion vectors
sparseFlowImg = prevImg.copy()
for i,(new,old) in enumerate(zip(currPoints,prevPoints)):
	a,b = new.ravel()
	c,d = old.ravel()
	if( a >= 0 and a < prevImg.shape[1] and b >= 0 and b < prevImg.shape[0]):
		sparseFlowImg = cv2.line(sparseFlowImg, (a,b),(c,d), (0,255,0), 1)

# write results		
cv2.imwrite("SparseFlow.png", sparseFlowImg)
		
# dense optical flow estimation
start = time.time();
flow = rlofProc.dense_flow(prevImg, currImg)
end = time.time();
print( "\nDense Optical Flow Estimation\n")
print( "#Features = " + str(prevImg.shape[0] * prevImg.shape[1]))
print( "Runtime[sec] = " + str(end - start ));
print("\n")

# draw optical flow field
hsv = np.zeros_like(prevImg)
hsv[...,2] = 255
mag, ang = cv2.cartToPolar(flow[...,0], flow[...,1])
hsv[...,0] = ang*180/np.pi/2
hsv[...,1] = cv2.normalize(mag,None,0,255,cv2.NORM_MINMAX)
denseFlowImg = cv2.cvtColor(hsv,cv2.COLOR_HSV2BGR)

#write results
cv2.imwrite("DenseFlow.png", denseFlowImg)