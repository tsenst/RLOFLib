cmake_minimum_required(VERSION 2.7)
project(RLOFApp)


set(LIBRLOF_INCLUDE "D:/Workspace/Senst/GIT/repo/C++/Optical\ Flow/OpticalFlowAlgorithms/RLOF/publish/" CACHE PATH " RLOF headers ")
set(LIBRLOF_PATH "D:/workspace/Senst/GIT/repo/C++/Optical\ Flow/OpticalFlowAlgorithms/cmake-build-release/" CACHE PATH " RLOF library file ")
set(OpenCV_DIR "D:/Workspace/Libs/opencv/build/MinGW/install/" CACHE PATH " OpenCV Install Path ")



FIND_PACKAGE( OpenCV REQUIRED )

#set (CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --allow-multiple-definition" )
include_directories(${LIBRLOF_INCLUDE} ${OpenCV_INCLUDE})

# standardized set compiler flags
add_definitions(-DHAVE_OPENMP )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES RLOFApp.cpp )

add_executable(RLOFApp ${SOURCE_FILES} )


if (MSVC)
    target_link_libraries(RLOFApp  LINK_PUBLIC
            ${OpenCV_LIBS} ${LIBRLOF_PATH}/libRLOF.lib )
else()
    target_link_libraries(RLOFApp  LINK_PUBLIC
            ${OpenCV_LIBS}
            ${LIBRLOF_PATH}/libRLOF.dll.a "-Wl,--allow-multiple-definition"
        )
endif()
#TARGET_LINK_LIBRARIES( RLOFLib LINK_PUBLIC ${Boost_LIBRARIES} )