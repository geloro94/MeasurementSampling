#include <algorithm>

#include "MeasurementSampler.h"

void MeasurementSampler::removeSamplesBefore(Instant startOfSampling, std::vector<Measurement>& unfilteredMeasurements)
{
	unfilteredMeasurements.erase(std::remove_if(unfilteredMeasurements.begin(), unfilteredMeasurements.end(), [&startOfSampling](const Measurement& msrmt)
		{
			return msrmt.getMeasurmentTime() < startOfSampling;
		}), unfilteredMeasurements.end());
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

	for (auto msrmt : unsampledMeasurements)
	{
		if (sortedSampledMeasurements.find(msrmt.getMeasurementType()) == sortedSampledMeasurements.end())
		{
			std::vector<Measurement> sampledMeasures{ msrmt };
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
