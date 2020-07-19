/*
 * Measurement.cpp
 *
 *  Created on: Jul 17, 2020
 *      Author: lorenz
 */

#include "Measurement.h"

Measurement::Measurement(Instant measurementTimePoint, MeasurementType measurementType, double measuredValue) :
	measurementTime(measurementTimePoint),
	measurementName(measurementType),
	measurementValue(measuredValue)
{

}

Measurement Measurement::createMeasurementFromString(const std::string& measurementStringRepresentation)
{
	auto mesurementString = measurementStringRepresentation.substr(1, measurementStringRepresentation.size() - 2);
	auto measurementInputParameters = HelperFunctions::split(mesurementString, ',');
	auto time = HelperFunctions::convertToTimePoint(measurementInputParameters[0], USED_TIME_FORMAT);
	auto type = measurementInputParameters[1];
	auto val = std::stod(measurementInputParameters[2]);
	return Measurement(time, type, val);

}

std::string Measurement::toSampledMeasurementString() const
{
	auto measurmentValueString = std::to_string(measurementValue);
	measurmentValueString.erase(measurmentValueString.find_last_not_of('0') + 1, std::string::npos );
	std::string measurementRep = "{" + HelperFunctions::convertToTimeString(getSampledTime(), USED_TIME_FORMAT) + ", " + measurementName + ", " +
			measurmentValueString + "}";
	return measurementRep;
}

std::string Measurement::toString() const
{
	auto measurmentValueString = std::to_string(measurementValue);
	measurmentValueString.erase(measurmentValueString.find_last_not_of('0') + 1, std::string::npos );
	std::string measurementRep = "{" + HelperFunctions::convertToTimeString(measurementTime, USED_TIME_FORMAT) + ", " + measurementName + ", " +
			measurmentValueString + "}";
	return measurementRep;
}

Instant Measurement::getMeasurmentTime() const
{
	return measurementTime;
}

Instant Measurement::getSampledTime() const
{
	// Has to be done in seconds to ensure the uint32_t cast of the count does not cut of the seconds: 5:01 -> 10 if cut off 5:01 -> 5
	return HelperFunctions::getSampledTimePoint<std::chrono::seconds>(getMeasurmentTime(), 300);
}


double Measurement::getMeasurementValue() const
{
	return measurementValue;
}

MeasurementType Measurement::getMeasurementType() const
{
	return measurementName;
}