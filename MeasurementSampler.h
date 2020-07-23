#ifndef MEASUREMENTSAMPLER_H_
#define MEASUREMENTSAMPLER_H_

#include <vector>
#include <map>

#include "Measurement.h"

class MeasurementSampler
{
public:
	std::map<MeasurementType, std::vector<Measurement>>  sample(Instant startOfSampling, std::vector<Measurement> unsampledMeasurements);
	void removeSamplesBefore(Instant startOfSampling, std::vector<Measurement>& unfilteredMeasurements);
	void sortChronological(std::vector<Measurement>& unsortedMeasurements);
	
};


#endif
