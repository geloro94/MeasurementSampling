cmake_minimum_required(VERSION 3.21)

project(MeasurementSampling)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Quellcode-Dateien auflisten
set(SOURCES
    src/main.cpp
    src/Measurement.cpp
    src/HelperFunctions.cpp
    src/MeasurementSampler.cpp
)

# Executable erstellen
add_executable(MeasurementSampling ${SOURCES})

# Enable testing
enable_testing()

# Add the test directory
add_subdirectory(test)