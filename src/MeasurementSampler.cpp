/*
 * MeasurementSampler.cpp
 *
 *  Created on: Jun 30, 2024
 *      Author: lorenz
 */

#include <algorithm>

#include "MeasurementSampler.h"

void MeasurementSampler::removeSamplesBefore_old(Instant startOfSampling, std::vector<Measurement>& unfilteredMeasurements)
{
	unfilteredMeasurements.erase(std::remove_if(unfilteredMeasurements.begin(), unfilteredMeasurements.end(), [&startOfSampling](const Measurement& msrmt)
		{
			return msrmt.getMeasurmentTime() < startOfSampling;
		}), unfilteredMeasurements.end());
}

void MeasurementSampler::removeSamplesBefore(Instant startOfSampling, std::vector<Measurement>& unfilteredMeasurements)
{
    std::erase_if(unfilteredMeasurements, [&startOfSampling](const Measurement& msrmt)
    {
        return msrmt.getMeasurmentTime() < startOfSampling;
    });
}


void MeasurementSampler::sortChronological(std::vector<Measurement>& unsortedMeasurements)
{
	std::sort(unsortedMeasurements.begin(), unsortedMeasurements.end(), [](const Measurement& lhs, const Measurement& rhs)
		{
			return (lhs.getMeasurmentTime() < rhs.getMeasurmentTime());
		});
}

std::map<MeasurementType, std::vector<Measurement>>  MeasurementSampler::sample(Instant startOfSampling,
	std::vector<Measurement> unsampledMeasurements)
{
    std::map<MeasurementType, std::vector<Measurement>> sortedSampledMeasurements;

    removeSamplesBefore(startOfSampling, unsampledMeasurements);

    sortChronological(unsampledMeasurements);

    for (const auto& msrmt : unsampledMeasurements)
    {
        auto& sampledMeasures = sortedSampledMeasurements[msrmt.getMeasurementType()];
        if (!sampledMeasures.empty() && sampledMeasures.back().getSampledTime() == msrmt.getSampledTime())
        {
            sampledMeasures.back() = msrmt;
        }
        else
        {
            sampledMeasures.push_back(msrmt);
        }
    }
    return sortedSampledMeasurements;
}
