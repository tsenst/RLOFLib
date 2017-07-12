cmake_minimum_required(VERSION 2.7)
project(RLOFApp)


set(LIBRLOF_INCLUDE ${PROJECT_SOURCE_DIR}/../include/ CACHE PATH " RLOF headers ")
set(LIBRLOF_PATH ${PROJECT_SOURCE_DIR}/../lib/ CACHE PATH " RLOF library file ")
set(OpenCV_DIR "" CACHE PATH " OpenCV Install Path ")



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
set (LINK_LIBRARY optimized ${LIBRLOF_PATH}/libRLOF_vc$(PlatformToolsetVersion)_$(PlatformName).lib debug ${LIBRLOF_PATH}/libRLOF_vc$(PlatformToolsetVersion)_$(PlatformName)d.lib)
	target_link_libraries(RLOFApp  
            ${OpenCV_LIBS}
            ${LINK_LIBRARY})
else()
    if( WIN32)
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set( RLOFLIB_NAME ${LIBRLOF_PATH}/libRLOF_MinGW64.dll.a)
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set( RLOFLIB_NAME ${LIBRLOF_PATH}/libRLOF_MinGW32.dll.a)
        endif()
    else()
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set( RLOFLIB_NAME ${LIBRLOF_PATH}/libRLOF_64.so)
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set( RLOFLIB_NAME ${LIBRLOF_PATH}/libRLOF_32.so)
        endif()
    endif()
	target_link_libraries(RLOFApp  LINK_PUBLIC
            ${OpenCV_LIBS}
            ${RLOFLIB_NAME} "-Wl,--allow-multiple-definition"
        )
endif()
