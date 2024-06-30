# Enable testing
enable_testing()

# Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# List of test files
set(TEST_SOURCES
    test_roundToNextMultiple.cpp
    test_convertToTimePoint.cpp
    test_sampledTimePoint.cpp
    test_inputFormat.cpp
    test_sample.cpp
    main.cpp  # Add main.cpp for the single test executable
)

# Add a single test executable
add_executable(AllTests ${TEST_SOURCES} ${PROJECT_SOURCE_DIR}/src/HelperFunctions.cpp ${PROJECT_SOURCE_DIR}/src/Measurement.cpp ${PROJECT_SOURCE_DIR}/src/MeasurementSampler.cpp)

# Link Google Test libraries
target_link_libraries(AllTests gtest gtest_main)

# Register the test executable with CTest
add_test(NAME AllTests COMMAND AllTests)

# Discover and register tests
include(GoogleTest)
gtest_discover_tests(AllTests)
