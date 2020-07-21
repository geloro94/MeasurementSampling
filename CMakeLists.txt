cmake_minimum_required(VERSION 3.10)

project(MeasurementSampling)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(MeasurementSampling main.cpp Measurement.cpp HelperFunctions.cpp)

include(CTest)

add_executable(test_roundToNextMultiple test_roundToNextMultiple.cpp HelperFunctions.cpp)

add_test(NAME test_roundToNextMultiple COMMAND test_roundToNextMultiple)

add_executable(test_convertToTimePoint test_convertToTimePoint.cpp HelperFunctions.cpp)

add_test(NAME test_convertToTimePoint COMMAND test_convertToTimePoint)

add_executable(test_sampledTimePoint test_sampledTimePoint.cpp HelperFunctions.cpp)

add_test(Name test_sampledTimePoint COMMAND test_sampledTimePoint)
