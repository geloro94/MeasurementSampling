/*
 * test_convertToTimePoint.cpp
 *
 *  Created on: Jun 30, 2024
 *      Author: lorenz
 */

#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <random>
#include "HelperFunctions.h"
#include "Measurement.h"

//Converting a random TimePoint to a string and back should equal the initial TimePoint
TEST(ConvertToTimePointTest, RandomTimePointConversion){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned long long> randomTimeDistribution(0, 65*365*24*60*60);

	for(int i = 0; i < 10000; i++)
	{
		std::chrono::system_clock::time_point randomTimepoint{};
		std::chrono::duration<unsigned long long> secondsSinceEpoche{ randomTimeDistribution(gen)};
		randomTimepoint = randomTimepoint + secondsSinceEpoche;
		auto convertedTimepointString = HelperFunctions::convertToTimePoint(HelperFunctions::convertToTimeString(randomTimepoint, USED_TIME_FORMAT), USED_TIME_FORMAT);
		{
			ASSERT_TRUE(randomTimepoint == convertedTimepointString) << "Test failed:" << HelperFunctions::convertToTimeString(randomTimepoint, USED_TIME_FORMAT) << " != " << HelperFunctions::convertToTimeString(HelperFunctions::convertToTimePoint(HelperFunctions::convertToTimeString(randomTimepoint, "%Y-%m-%dT%H:%M:%S"), "%Y-%m-%dT%H:%M:%S"), "%Y-%m-%dT%H:%M:%S");
		}
	}
}

//Converting Fixed TimePoints to a string and back should equal the initial TimePoint
TEST(ConvertToTimePointTest, FixedTimePointConversion){
	std::vector<std::string> timePoints{"2024-06-30T00:00:00", "1970-01-01T01:00:00", "1960-01-01T00:00:00", "2024-02-29T00:00:00", "9999-12-31T23:59:59"};
	for(const auto& timePoint : timePoints)
	{
		auto convertedTimepointString = HelperFunctions::convertToTimeString(HelperFunctions::convertToTimePoint(timePoint, "%Y-%m-%dT%H:%M:%S"), "%Y-%m-%dT%H:%M:%S");
		std::cout << "Converted TimePoint: " << convertedTimepointString << std::endl;
		{
			ASSERT_TRUE(timePoint == convertedTimepointString) << "Test failed:" << timePoint << " != " << convertedTimepointString;
		}
	}
}




