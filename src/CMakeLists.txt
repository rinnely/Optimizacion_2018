cmake_minimum_required (VERSION 2.6)
project (Trabajo_final)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -fopenmp -Wall -lopencv_core -lgdal -lopencv_imgproc -lopencv_flann -lopencv_highgui -lopencv_imgcodecs")

add_executable(
        distance.cpp
        main.cpp
        DisplayImage.cpp)
