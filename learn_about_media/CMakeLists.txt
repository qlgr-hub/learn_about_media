cmake_minimum_required(VERSION 3.26)

project(lam)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./include)
set(FFmpegLibs avcodec avformat avdevice avfilter avutil swresample swscale)
aux_source_directory(./source/usingff USINGFF_SRCS)

add_library(lam SHARED ${USINGFF_SRCS})
set_target_properties(lam PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(lam ${FFmpegLibs})


add_executable(demux_decode ./examples/demux_decode/main.cxx)
target_include_directories(demux_decode PUBLIC ./include)
target_link_libraries(demux_decode lam)
