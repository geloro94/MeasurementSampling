/*
 * Measurement.h
 *
 *  Created on: Jun 30, 2024
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

	//Creates a string representation using the sampledTimePoint
	std::string toSampledString() const;
	
	Instant getMeasurmentTime() const;
	double getMeasurementValue() const;
	MeasurementType getMeasurementType() const;

	//Returns the closest Instant which is a multiple of 5 minutes to the measurementTime. If the measuremtentTime itself is a multiple of 5 the values are equal
	Instant getSampledTime() const;

private:
	Instant measurementTime;
	MeasurementType measurementName;
	double measurementValue;
};

#endif /* MEASUREMENT_H_ */
