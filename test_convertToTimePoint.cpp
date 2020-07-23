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
#include "Measurement.h"

//Converting a random TimePoint to a string and back should equal the initial TimePoint


int main()
{
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
			if(randomTimepoint == convertedTimepointString)
			{
				continue;
			}
			else
			{
				std::cout << "Test failed:" << HelperFunctions::convertToTimeString(randomTimepoint, USED_TIME_FORMAT) << " != " << HelperFunctions::convertToTimeString(HelperFunctions::convertToTimePoint(HelperFunctions::convertToTimeString(randomTimepoint, "%Y-%m-%dT%H:%M:%S"), "%Y-%m-%dT%H:%M:%S"), "%Y-%m-%dT%H:%M:%S");
				return -1;
			}
		}
	}
	std::cout << "Test passed";
	return 0;
}


