

image1 = imread('../Doc/ErnstReuter1.png');
image2 = imread('../Doc/ErnstReuter2.png');

pointlist1 = [ 1 10 14 17 ; 5 100 4 30];

% perform an accuracy test of each PLK/RLOF implementation
% define parameter
parameter = struct('maxLevel', 5, 'maxIter', 30, 'HampelNormS0', 3.2, 'HampelNormS1', 7, ...
    'LargeWinSize', 21 , 'SmallWinSize', 9, 'MinEigenvalue', 0.001, 'RansacReprojThresholdPercentil' , 71, ...
    'SegmentationThreshold', 30, 'useIlluminationModel' , 1, 'useGlobalMotionPrior', 1, ...
    'SupportRegionType', 'SR_FIXED', 'SolverType', 'ST_BILINEAR', ...
    'options', 'PrintParameter' );

% demo estimates and validates the motion vector for each PLK/RLOF derivate
idx = 1;



gridSize = 10;
noRows = size(image1,1);
noCols = size(image1,2);
% initialize pointlist with features to track
[Y,X] = meshgrid(0:gridSize:noRows-1, 0:gridSize:noCols-1);
pointlist1 = [reshape(X, size(X,1) * size(X,2), 1)'; reshape(Y, size(Y,1) * size(Y,2), 1)' ];
%track features
pointlist2 = mex_SparseRLOF(image1, image2, pointlist1, parameter);
% draw result
imagesc(image1);
for i = 1:size(pointlist2,2)
    line([pointlist1(1,i) pointlist2(1,i)], [pointlist1(2,i) pointlist2(2,i)]);
end

tic
[U, V] = mex_DenseRLOF(image1, image2, parameter);
toc
figure
imagesc(U);