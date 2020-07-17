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
#include "HelperFunctions.h"

namespace HelperFunctions{


std::vector<std::string> split(const std::string& str, char delim)
{
    std::stringstream ss{str};
    std::string word;
    std::vector<std::string> result;
    while (std::getline(ss, word, delim)) {
    	result.push_back(word);
    }
    return result;
}

// Refer to https://en.cppreference.com/w/cpp/io/manip/get_time for possible timepointStringFormats
std::chrono::system_clock::time_point convertToTimePoint(std::string timepointString, std::string timeStringFormat)
{
	std::chrono::system_clock::time_point tp{};
	std::tm time{};
    std::istringstream ss(timepointString);

    if (ss >> std::get_time(&time, timeStringFormat.c_str()))
    {
    	 auto timestemp = std::mktime(&time);
    	 tp = std::chrono::system_clock::from_time_t(timestemp);
    }

	return tp;
}

std::string convertToTimeString(std::chrono::system_clock::time_point tp, std::string timeStringFormat)
{
	auto timestemp = std::chrono::system_clock::to_time_t(tp);
    std::tm tm = *std::localtime(&timestemp);
    std::stringstream ss;
    ss << std::put_time( &tm, timeStringFormat.c_str() );
    return ss.str();
}

uint32_t roundUpToNextMultipleOf(uint32_t number, uint32_t factor)
{
	return ((number + factor-1) / factor )* factor;
}

} //namespace HelperFunctions


