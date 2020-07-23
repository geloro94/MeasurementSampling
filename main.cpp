/*
 * main.cpp
 *
 *  Created on: Jul 17, 2020
 *      Author: lorenz
 */

#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <regex>
#include <fstream>

#include "Measurement.h"
#include "HelperFunctions.h"
#include "MeasurementSampler.h"



int main(int argc, char *argv[])
{
	std::string filepath{"UnsampledMeasurements.txt"};
	if (argc == 2)
	{
		filepath = argv[1];
	}
	std::string regexString = R"(^\{((19|20)\d\d-(0[1-9]|1[012])-([012]\d|3[01])T([01]\d|2[0-3]):([0-5]\d):([0-5]\d)),\w*,(-?)(0|([1-9][0-9]*))(\.[0-9]+)?\}$)";
	std::regex regularExpression{regexString.c_str()};
	std::ifstream measurementDataFile{filepath};
	std::vector<Measurement> unsampledMeasurements{};
	std::string line;
	if(measurementDataFile) {
		while(std::getline(measurementDataFile, line))
		{
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
			if(std::regex_match(line, regularExpression)) //!line.empty()
			{
				auto msrmt = Measurement::createMeasurementFromString(line);
				unsampledMeasurements.emplace_back(msrmt);
			}
			else
			{
				if (!line.empty())
				{
					std::cout << "invalid input: " << line << " did not match the expected data format\n";
				}
			}
		}
	}
	else
	{
		std::cout << "Could not open " << filepath << std::endl;
	}

	MeasurementSampler sampler{};
	auto sampledMeasurements = sampler.sample(HelperFunctions::convertToTimePoint("", USED_TIME_FORMAT), unsampledMeasurements);

	for (auto& value : sampledMeasurements)
	{
		for(auto & msrmt : value.second)
		{
			std::cout << msrmt.toSampledString() << std::endl;
		}
	}


	return 0;
}

