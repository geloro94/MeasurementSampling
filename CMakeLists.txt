cmake_minimum_required(VERSION 3.10)

project(MeasurementSampling)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



add_executable(MeasurementSampling main.cpp Measurement.cpp HelperFunctions.cpp)