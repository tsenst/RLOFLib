# Matlab Mex-Function
The RLOFLib provide two Matlab mex functions:

  [U, V] = mex_DenseRLOF(image1,image2);
  [U, V] = mex_DenseRLOF(image1,image2, parameter);
  
mex_DenseRLOF to compute dense optical flow fields and 

	pointlist2 = mex_SparseRLOF(image1,image2, pointlist1);
	pointlist2 = mex_SparseRLOF(image1,image2, pointlist1, parameter);
	
mex_SparseRLOF to track a set of predefined points based on the sparse RLOF estimation.
Both mex files have been compiled with Matlab 15a and the Microsoft Visual C++ 2013 Professional compiler. 