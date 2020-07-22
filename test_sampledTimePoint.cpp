/*
 * test_sampledTimePoint.cpp
 *
 *  Created on: Jul 21, 2020
 *      Author: lorenz
 */

#include <random>
#include <iostream>
#include <chrono>

#include "HelperFunctions.h"

int main()
{
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
		if (sampledMinutesCount%5 == 0)
		{
			if ((sampledTimepoint - randomTimepoint) < std::chrono::duration<double, std::ratio<60>>{5})
			{
				continue;
			}
			else
			{
				std::cout << "Test Failed: " << HelperFunctions::convertToTimeString(sampledTimepoint, "%Y-%m-%dT%H:%M:%S") << "-" << HelperFunctions::convertToTimeString(randomTimepoint, "%Y-%m-%dT%H:%M:%S") << ">" << std::to_string(5) << std::endl;
				return -1;
			}
		}
		else
		{
			std::cout << "Test Failed: " << HelperFunctions::convertToTimeString(sampledTimepoint, "%Y-%m-%dT%H:%M:%S") << ": " << sampledMinutesCount << "modulo" << std::to_string(5) << "unequal 0." << std::endl;
			return -1;
		}
	}

	for(int i = 0; i < 12*24; i++)
	{
		std::chrono::system_clock::time_point mulitple5Timepoint{};
		std::chrono::duration<unsigned long long> secondsSinceEpoche{i*5*60};
		mulitple5Timepoint = mulitple5Timepoint + secondsSinceEpoche;
		using minutes = std::chrono::duration<double, std::ratio<60>>;
		if(HelperFunctions::getSampledTimePoint<minutes>(mulitple5Timepoint, 5) == mulitple5Timepoint)
		{
			//std::cout << HelperFunctions::convertToTimeString(mulitple5Timepoint, "%Y-%m-%dT%H:%M:%S") << std::endl;
			continue;
		}
		else
		{
			std::cout << "Test Failed: " << HelperFunctions::convertToTimeString(mulitple5Timepoint, "%Y-%m-%dT%H:%M:%S") << std::endl;
		}
	}
	std::cout << "Test passed" << std::endl;
	return 0;
}
