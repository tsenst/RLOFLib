# Example Application
This small sample project demonstrates the application of the RLOF interface for computing a dense optical flow field.
The demo loads two images, which can be passed by the input arguments or are the Ernstreuter images in the doc folder, 
computes the dense optical flow field and write the results as color coded image to Flow.png.

The sample project can be build with cmake-gui (from Version 2.7). Please set the following options:
 - LIBRLOF_INCLUDE -> directing to the include directory containing the files RLOF_Flow.h and RLOF_Parameter.h
 - LIBRLOF_PATH 	-> directing to the lib directory containing libRLOF_X lib files
 - OpenCV_DIR 		-> directing to your local opencv directory.

 ## Compile with Visual Studio  
Run cmake-gui and select a build folder to create the visual studio solution file.
The example application has been tested with the following configurations:
 - [x] Visual Studio 2010 / Windows 7
 - [x] Visual Studio 2017 / Windows 7

If your current Visual Studio version is not supported. You can try to link sibiling existing version.
The following configurations have been tested:
 - [x] Visual Studio 2015 link libRLOF_vc141_x64.lib / Windows 10

Please feel free to contact us (senst@nue.tu-berlin.de) if you need a specific compilant for your development enviroment. 
 
Please mention to announce the binary path "/lib/" e.g. by setting the environment PATH variable
(e.g. PATH=D:/workspace/Arbeit_Senst/publicProjects/RLOFLib/lib/ ) in your project debugging settings.

## Compile with Linux
You can build and run the sample project by using cmake as follows:

	mkdir build
	cd build
	cmake ../
	make -j
	./RLOFApp