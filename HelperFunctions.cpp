/*
 * HelperFunctions.cpp
 *
 *  Created on: Jul 17, 2020
 *      Author: lorenz
 */

#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cmath>
#include "HelperFunctions.h"

namespace HelperFunctions{


std::vector<std::string> split(const std::string& str, char delim)
{
    std::stringstream ss{str};
    std::string word{};
    std::vector<std::string> result;
    while (std::getline(ss, word, delim)) {
    	result.push_back(word);
    }
    return result;
}

// Refer to https://en.cppreference.com/w/cpp/io/manip/get_time for possible timepointStringFormats
std::chrono::system_clock::time_point convertToTimePoint(std::string timepointString, std::string timeStringFormat)
{
	//use UTC timestamps
	setenv("TZ", "UTC", 1);
	std::chrono::system_clock::time_point tp{};
	std::tm time{};
	std::istringstream ss(timepointString);

    if (ss >> std::get_time(&time, timeStringFormat.c_str()))
    {
    	auto timestamp = std::mktime(&time);
    	tp = std::chrono::system_clock::from_time_t(timestamp);
    }

	return tp;
}

std::string convertToTimeString(std::chrono::system_clock::time_point tp, std::string timeStringFormat)
{
	auto timestamp = std::chrono::system_clock::to_time_t(tp);
    auto tm = *std::localtime(&timestamp);
    std::stringstream ss;
    ss << std::put_time( &tm, timeStringFormat.c_str() );
    return ss.str();
}

int64_t roundUpToNextMultipleOf(double number, uint32_t factor)
{
	// Next Multiple of 0 equals 0?
	if(factor == 0)
	{
		return 0;
	}
	return static_cast<int64_t>((ceil(number / factor ))* factor);
}

} //namespace HelperFunctions


