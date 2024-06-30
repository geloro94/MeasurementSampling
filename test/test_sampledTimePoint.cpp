/*
 * test_sampledTimePoint.cpp
 *
 *  Created on: Jun 30, 2024
 *      Author: lorenz
 */
#include <gtest/gtest.h>
#include <random>
#include <iostream>
#include <chrono>

#include "HelperFunctions.h"
#include "Measurement.h"

TEST(SampleTimePointTest, RandomTimePoint) {
		std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned long long> randomTimeDistribution(0, 65*365*24*60*60);

	for (int i=0; i < 10000; i++)
	{
		std::chrono::system_clock::time_point randomTimepoint{};
		std::chrono::duration<unsigned long long> secondsSinceEpoche{ randomTimeDistribution(gen)};
		randomTimepoint = randomTimepoint + secondsSinceEpoche;
		using minutes = std::chrono::duration<double, std::ratio<60>>;
		auto sampledTimepoint = HelperFunctions::getSampledTimePoint<minutes>(randomTimepoint, 5);
		auto sampledMinutesCount = std::chrono::duration_cast<std::chrono::minutes>(sampledTimepoint.time_since_epoch()).count();
		ASSERT_TRUE(sampledMinutesCount%5 == 0) << "Test Failed: " << HelperFunctions::convertToTimeString(sampledTimepoint, USED_TIME_FORMAT) << ": " << sampledMinutesCount << "modulo" << std::to_string(5) << "unequal 0." << std::endl;
		constexpr auto fiveMinutes = std::chrono::duration<double, std::ratio<60>>{5};
		ASSERT_TRUE((sampledTimepoint - randomTimepoint) < fiveMinutes) << "Test Failed: " << HelperFunctions::convertToTimeString(sampledTimepoint, USED_TIME_FORMAT) << "-" << HelperFunctions::convertToTimeString(randomTimepoint, USED_TIME_FORMAT) << ">" << std::to_string(5) << std::endl;
	}

	for(int i = 0; i < 12*24; i++)
	{
		std::chrono::system_clock::time_point mulitple5Timepoint{};
		std::chrono::duration<unsigned long long> secondsSinceEpoche{i*5*60};
		mulitple5Timepoint = mulitple5Timepoint + secondsSinceEpoche;
		using minutes = std::chrono::duration<double, std::ratio<60>>;
		ASSERT_TRUE(HelperFunctions::getSampledTimePoint<minutes>(mulitple5Timepoint, 5) == mulitple5Timepoint) << "Test Failed: " << HelperFunctions::convertToTimeString(mulitple5Timepoint, USED_TIME_FORMAT) << std::endl;
	}
}

TEST(SampleTimePointTest, FixedTimePoints)
{
	std::unordered_map<std::string, std::string> timePoints{
		{"2024-06-30T00:00:01", "2024-06-30T00:05:00"},
		{"2024-06-30T00:04:49", "2024-06-30T00:05:00"},
		{"2024-06-30T00:05:00", "2024-06-30T00:05:00"},
		{"2024-06-30T23:59:00", "2024-07-01T00:00:00"}
	};
	for(const auto& timePoint : timePoints)
	{
		auto convertedTimepointString = HelperFunctions::convertToTimeString(HelperFunctions::getSampledTimePoint<std::chrono::seconds>(HelperFunctions::convertToTimePoint(timePoint.first, USED_TIME_FORMAT), 300), USED_TIME_FORMAT);
		ASSERT_TRUE(timePoint.second == convertedTimepointString) << "Test failed:" << timePoint.second << " != " << convertedTimepointString;
	}
}

TEST(SampleTimePointTest, LeapYear)
{
	std::unordered_map<std::string, std::string> timePoints{
		{"2024-02-28T23:59:00", "2024-02-29T00:00:00"},
		{"2024-02-29T23:59:00", "2024-03-01T00:00:00"}
	};
	for(const auto& timePoint : timePoints)
	{
		auto convertedTimepointString = HelperFunctions::convertToTimeString(HelperFunctions::getSampledTimePoint<std::chrono::seconds>(HelperFunctions::convertToTimePoint(timePoint.first, USED_TIME_FORMAT), 300), USED_TIME_FORMAT);
		ASSERT_TRUE(timePoint.second == convertedTimepointString) << "Test failed:" << timePoint.second << " != " << convertedTimepointString;
	}
}
