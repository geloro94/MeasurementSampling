/*
 * test_convertToTimePoint.cpp
 *
 *  Created on: Jul 21, 2020
 *      Author: lorenz
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <random>
#include "HelperFunctions.h"

int main()
{
	setenv("TZ", "UTC", 1);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned long long> randomDoubleDistribution(0, 65*365*24*60*60);

	for(int i = 0; i < 10000; i++)
	{
		std::chrono::system_clock::time_point sampledTimepoint{};
		std::chrono::duration<unsigned long long> secondsSinceEpoche{randomDoubleDistribution(gen)};
		sampledTimepoint = sampledTimepoint + secondsSinceEpoche;
		auto convertedTimepointString = HelperFunctions::convertToTimePoint(HelperFunctions::convertToTimeString(sampledTimepoint, "%Y-%m-%dT%H:%M:%S"), "%Y-%m-%dT%H:%M:%S");
		{
			if(sampledTimepoint == convertedTimepointString)
			{
				continue;
			}
			else
			{
				std::cout << "Test failed:" << HelperFunctions::convertToTimeString(sampledTimepoint, "%Y-%m-%dT%H:%M:%S") << " != " << HelperFunctions::convertToTimeString(HelperFunctions::convertToTimePoint(HelperFunctions::convertToTimeString(sampledTimepoint, "%Y-%m-%dT%H:%M:%S"), "%Y-%m-%dT%H:%M:%S"), "%Y-%m-%dT%H:%M:%S");
				return -1;
			}
		}
	}
	std::cout << "Test passed";
	return 0;
}


