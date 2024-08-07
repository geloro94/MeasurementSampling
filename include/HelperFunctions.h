#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <string>
#include <vector>
#include <chrono>

namespace HelperFunctions{
//Splits an input string based on the delimiter character
std::vector<std::string> split(const std::string& str, char delim);

//Creates a time_point based on the input timepointString and the timeStringFormat
//Refer to https://en.cppreference.com/w/cpp/io/manip/get_time for possible timepointStringFormats
std::chrono::system_clock::time_point convertToTimePoint(std::string timepointString, std::string timeStringFormat);

// Converts the input time-point into a string based on the given timeStringFormat
std::string convertToTimeString(std::chrono::system_clock::time_point tp, std::string timeStringFormat);

// Rounds the input number to the next multiple of of the given factor
int64_t roundUpToNextMultipleOf(double number, uint32_t factor);

//Samples the given time-point to a raster defined by the duration time and the sampleFactor i.e. durationType = std::duration<double, ratio<60>> and sampleFactor 5 -> every 5 mins.
//Care if you use the built in std::minutes: Because of the duration cast every value below the duration_type will be ignored: Example 5:01 -> 5. To ensure 5:01 -> 10 use std::chrono::seconds and the according sampleFactor or use std::duration<double, std::ratio<60>>
template <typename durationType>
std::chrono::system_clock::time_point getSampledTimePoint(std::chrono::system_clock::time_point toSampleTime, uint32_t sampleFactor, int offset = 0)
{
	double duration_count_since_epoche = std::chrono::duration_cast<durationType>(toSampleTime.time_since_epoch()).count()-offset;
	int64_t duration_count_since_epoche_sampled = roundUpToNextMultipleOf(duration_count_since_epoche, sampleFactor)+offset;
	auto durationSinceEpoche = std::chrono::duration_cast<std::chrono::duration<int>>(durationType{ duration_count_since_epoche_sampled });
	std::chrono::system_clock::time_point sampledTimepoint{};
	sampledTimepoint = sampledTimepoint + durationSinceEpoche;
	return sampledTimepoint;
}

} //namespace HelperFunctions

#endif
