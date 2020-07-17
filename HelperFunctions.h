#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <string>
#include <vector>
#include <chrono>

namespace HelperFunctions{
std::vector<std::string> split(const std::string& str, char delim);

// Refer to https://en.cppreference.com/w/cpp/io/manip/get_time for possible timepointStringFormats
std::chrono::system_clock::time_point convertToTimePoint(std::string timepointString, std::string timeStringFormat);

std::string convertToTimeString(std::chrono::system_clock::time_point tp, std::string timeStringFormat);

uint32_t roundUpToNextMultipleOf(uint32_t number, uint32_t factor);

//Samples the given timepoint to a raster defined by the duration time and the sampleFactor i.e. durationType = std::chrono::minutes and sampleFactor 5 -> every 5 mins.
//Because of a implicit conversion to uint32_t the time resolutions might be ignored for the given example 5:01 -> 5. To ensure 5:01 -> 10 use std::chrono::seconds and the according sampleFa
template <typename durationType>
std::chrono::system_clock::time_point getSampledTimePoint(std::chrono::system_clock::time_point toSampleTime, uint32_t sampleFactor)
{
	uint32_t minutes_since_epoche = std::chrono::duration_cast<durationType>(toSampleTime.time_since_epoch()).count();
	uint32_t minutes_since_epoche_sampled = roundUpToNextMultipleOf(minutes_since_epoche, sampleFactor);
	auto durationSinceEpoche = durationType{minutes_since_epoche_sampled};
	std::chrono::system_clock::time_point sampledTimepoint{};
	sampledTimepoint = sampledTimepoint + durationSinceEpoche;
	return sampledTimepoint;
}

} //namespace HelperFunctions

#endif
