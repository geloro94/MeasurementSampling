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

#include "Measurement.h"
#include "HelperFunctions.h"

void removeSamplesBefore(Instant startOfSampling, std::vector<Measurement>& unfilteredMeasurements)
{
	unfilteredMeasurements.erase(std::remove_if(unfilteredMeasurements.begin(), unfilteredMeasurements.end(), [&startOfSampling](const Measurement& msrmt)
	{
		return msrmt.getMeasurmentTime() < startOfSampling;
	}), unfilteredMeasurements.end());
}

void sortSamples(std::vector<Measurement>& unsortedMeasurements)
{
	std::sort(unsortedMeasurements.begin(), unsortedMeasurements.end(), [](const Measurement& lhs, const Measurement& rhs)
	{
		return (lhs.getMeasurmentTime() < rhs.getMeasurmentTime());
	});
}

std::map<MeasurementType, std::vector<Measurement>> sample(Instant startOfSampling,
		std::vector<Measurement> unsampledMeasurements)
{
	std::map<MeasurementType, std::vector<Measurement>> sortedSampledMeasurements;

	removeSamplesBefore(startOfSampling, unsampledMeasurements);

	sortSamples(unsampledMeasurements);

	for(auto& msrmt : unsampledMeasurements)
	{
		if (sortedSampledMeasurements.find(msrmt.getMeasurementType()) == sortedSampledMeasurements.end())
		{
			std::vector<Measurement> sampledMeasures{msrmt};
			sortedSampledMeasurements[msrmt.getMeasurementType()] = sampledMeasures;
		}
		else
		{
			auto& sampledMeasures = sortedSampledMeasurements[msrmt.getMeasurementType()];
			if (sampledMeasures.back().getSampledTime() == msrmt.getSampledTime())
			{
				sampledMeasures.back() = msrmt;
			}
			else
			{
				sampledMeasures.push_back(msrmt);
			}
		}
	}
	return sortedSampledMeasurements;
}

int main()
{
	std::string regexString = R"(^\{((19|20)\d\d-(0[1-9]|1[012])-([012]\d|3[01])T([01]\d|2[0-3]):([0-5]\d):([0-5]\d)),\w*,(-?)(0|([1-9][0-9]*))(\.[0-9]+)?\}$)";
	std::regex regularExpression{regexString.c_str()};
	std::string measurementData = R"(
	{2017-05-03T10:04:45, TEMP, 35.79}
	{2017-05-03T10:04:45, TEMP, 35.79}
	{2017-01-03T10:01:18, SPO2, 98.78}
	{2017-01-03T10:09:07, TEMP, 35.01}
	{2017-01-03T10:03:34, SPO2, 96.49}
	{2017-01-03T10:02:01, TEMP, 35.82}
	{2017-01-03T10:05:00, SPO2, 97.17}
	{2017-01-03T10:05:01, SPO2, 95.08}
	)";

	std::vector<Measurement> unsampledMeasurements{};
	std::istringstream input(measurementData);
	std::string line;
	while(std::getline(input, line))
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


	auto sampledMeasurements = sample(HelperFunctions::convertToTimePoint("", USED_TIME_FORMAT), unsampledMeasurements);

	for (auto& value : sampledMeasurements)
	{
		for(auto & msrmt : value.second)
		{
			std::cout << msrmt.toSampledMeasurementString() << std::endl;
		}
	}


	return 0;
}

