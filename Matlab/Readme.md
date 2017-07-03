# Matlab Mex-Function
The RLOFLib provides two Matlab mex functions.
The function mex_DenseRLOF to compute dense optical flow field [U,V] and

  	[U, V] = mex_DenseRLOF(image1,image2);
  	[U, V] = mex_DenseRLOF(image1,image2, parameter);
  
the function mex_SparseRLOF to track a set of given points (pointlist1) based on the sparse RLOF estimation.

	pointlist2 = mex_SparseRLOF(image1,image2, pointlist1);
	pointlist2 = mex_SparseRLOF(image1,image2, pointlist1, parameter);
	

Both mex files have been compiled with Matlab 15a and the Microsoft Visual C++ 2013 Professional compiler. 
