cmake_minimum_required(VERSION 3.10)

project(MeasurementSampling)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(MeasurementSampling main.cpp Measurement.cpp HelperFunctions.cpp "MeasurementSampler.cpp")

include(CTest)

add_executable(test_roundToNextMultiple test_roundToNextMultiple.cpp HelperFunctions.cpp)

add_test(NAME test_roundToNextMultiple COMMAND test_roundToNextMultiple)

add_executable(test_convertToTimePoint test_convertToTimePoint.cpp HelperFunctions.cpp)

add_test(NAME test_convertToTimePoint COMMAND test_convertToTimePoint)

add_executable(test_sampledTimePoint test_sampledTimePoint.cpp HelperFunctions.cpp)

add_test(NAME test_sampledTimePoint COMMAND test_sampledTimePoint)

add_executable(test_inputFormat test_inputFormat.cpp HelperFunctions.cpp)

add_test(NAME test_inputFormat COMMAND test_inputFormat)

add_executable(test_sample test_sample.cpp HelperFunctions.cpp Measurement.cpp "MeasurementSampler.cpp")

add_test(NAME test_sample COMMAND test_sample)
