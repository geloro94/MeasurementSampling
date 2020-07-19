/*
 * Measurement.h
 *
 *  Created on: Jul 17, 2020
 *      Author: lorenz
 */

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include <string>
#include <chrono>
#include <iostream>
#include "HelperFunctions.h"


using Instant = std::chrono::system_clock::time_point;
using MeasurementType = std::string;

const std::string USED_TIME_FORMAT = "%Y-%m-%dT%H:%M:%S";

class Measurement {
public:
	static Measurement createMeasurementFromString(const std::string& measurementStringRepresentation);

	Measurement(Instant measurementTimePoint, MeasurementType measurementType, double measuredValue);
	~Measurement() = default;
	Measurement(const Measurement&) = default;
	Measurement(Measurement&&) = default;
	Measurement& operator=(const Measurement&) = default;
	Measurement& operator=(Measurement&&) = default;

	std::string toString() const;
	std::string toSampledMeasurementString() const;
	
	const Instant getMeasurmentTime() const;
	const double getMeasurementValue() const;
	const MeasurementType getMeasurementType() const;
	const Instant getSampledTime() const;

private:
	Instant measurementTime;
	MeasurementType measurementName;
	double measurementValue;
};

#endif /* MEASUREMENT_H_ */
