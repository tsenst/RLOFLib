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

if( MSVC )
    set( RLOFLIB_NAME ${LIBRLOF_PATH}"/libRLOF_vc$(PlatformToolsetVersion)_$(PlatformName).lib")
else()
    if( WIN32)
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set( RLOFLIB_NAME ${LIBRLOF_PATH}"/RLOF_MinGW64.dll.a")
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set( RLOFLIB_NAME ${LIBRLOF_PATH}"/RLOF_MinGW32.dll.a")
        endif()
    else()
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set( RLOFLIB_NAME ${LIBRLOF_PATH}"/RLOF_64.a")
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set( RLOFLIB_NAME ${LIBRLOF_PATH}"/RLOF_32.a")
        endif()
    endif()
endif()

target_link_libraries(RLOFApp  LINK_PUBLIC
            ${OpenCV_LIBS}
            ${LIBRLOF_PATH} "-Wl,--allow-multiple-definition"
        )
