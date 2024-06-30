#include <gtest/gtest.h>
#include <random>

#include "HelperFunctions.h"
#include "Measurement.h"
#include "MeasurementSampler.h"

//The sampled measurement should have vectors of only the given key type of the sampled map.
//All values should be after the starting time-point
//All values should be sorted chronological
//Only one value should be sampled per Interval
TEST(SampleTest, RandomSample) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned long long> randomTimeDistribution(50 * 365 * 24 * 60 * 60, 50 * 365 * 24 * 60 * 60 + 24*60*60); //all values within 24 hours
	std::uniform_int_distribution<> index(0, 3);
	std::uniform_real_distribution<double> randomDoubleDistribution(-10000, 10000);
	std::vector<std::string> msrmtTypes{ "SPO2", "HEARTRATE", "TEMP", "BPM" };

	for (int i = 0; i < 1000; i++)
	{
		std::vector<Measurement> randomUnsampledMeasurements{};
		for (int j= 0; j < 200; j++)
		{
			std::chrono::system_clock::time_point randomTimepoint{};
			std::chrono::duration<unsigned long long> secondsSinceEpoche{ randomTimeDistribution(gen) };
			randomTimepoint = randomTimepoint + secondsSinceEpoche;

			auto randomInput = "{" + HelperFunctions::convertToTimeString(randomTimepoint, USED_TIME_FORMAT) + "," + msrmtTypes[index(gen)] + "," + std::to_string(randomDoubleDistribution(gen)) + "}";
			auto randomMsrmt = Measurement::createMeasurementFromString(randomInput);
			randomUnsampledMeasurements.emplace_back(randomMsrmt);
		}

		MeasurementSampler sampler{};

		std::chrono::system_clock::time_point randomstartTimepoint{};
		std::chrono::duration<unsigned long long> secondsSinceEpoche{ randomTimeDistribution(gen) - 24*60*60};
		randomstartTimepoint = randomstartTimepoint + secondsSinceEpoche;

		auto sampledMeasurements = sampler.sample(randomstartTimepoint, randomUnsampledMeasurements);

		if (sampledMeasurements.empty())
		{
			for(const auto& msrmt : randomUnsampledMeasurements)
			{
				ASSERT_TRUE(msrmt.getMeasurmentTime() > randomstartTimepoint) << "Test Failed: Measurements were not sampled" << std::endl;
			}
		}
		
		for (auto& value : sampledMeasurements)
		{
			Instant lastsampledTimePoint{};
			for (auto& msrmt : value.second)
			{
				//Check vector for each type
				ASSERT_TRUE(msrmt.getMeasurementType() == value.first) << "Test Failed: " << "Sampled Value in the Wrong column: " << msrmt.toSampledString() << value.first << std::endl;
				//Check all values before startPoint are ignored
				ASSERT_TRUE(msrmt.getMeasurmentTime() > randomstartTimepoint) << "Test Failed: " << "Sampled Value before samplingStartPoint: " << msrmt.toSampledString() << HelperFunctions::convertToTimeString(randomstartTimepoint, USED_TIME_FORMAT) << std::endl;
				//Check every consecutive MeasuremmentTime has to be larger than the last sampled one
				ASSERT_TRUE(msrmt.getMeasurmentTime() > lastsampledTimePoint) << "Test Failed: " << msrmt.toSampledString() << std::endl;
				constexpr auto fiveMinutes = std::chrono::duration<double, std::ratio<60>>{5};
				ASSERT_TRUE(msrmt.getSampledTime() - lastsampledTimePoint >= fiveMinutes) << "Test Failed: " << msrmt.toSampledString() << std::endl;
				lastsampledTimePoint = msrmt.getSampledTime();
				//std::cout << msrmt.toSampledString() << std::endl;
			}
		}

	}
	std::cout << "Test passed" << std::endl;
}

TEST(SampleTest, FixedSample) {
    std::vector<Measurement> fixedUnsampledMeasurements{
        Measurement::createMeasurementFromString("{2017-01-03T10:04:45, TEMP, 35.79}"),
        Measurement::createMeasurementFromString("{2017-01-03T10:01:18, SPO2, 98.78}"),
        Measurement::createMeasurementFromString("{2017-01-03T10:09:07, TEMP, 35.01}"),
        Measurement::createMeasurementFromString("{2017-01-03T10:03:34, SPO2, 96.49}"),
        Measurement::createMeasurementFromString("{2017-01-03T10:02:01, TEMP, 35.82}"),
        Measurement::createMeasurementFromString("{2017-01-03T10:05:00, SPO2, 97.17}"),
        Measurement::createMeasurementFromString("{2017-01-03T10:05:01, SPO2, 95.08}")
    };

    MeasurementSampler sampler{};
    auto result = sampler.sample(HelperFunctions::convertToTimePoint("2017-01-03T10:00:00", USED_TIME_FORMAT), fixedUnsampledMeasurements);
    auto expected = std::map<std::string, std::vector<Measurement>>{
        {"SPO2", {Measurement::createMeasurementFromString("{2017-01-03T10:05:00, SPO2, 97.17}"), Measurement::createMeasurementFromString("{2017-01-03T10:10:00, SPO2, 95.08}")}},
        {"TEMP", {Measurement::createMeasurementFromString("{2017-01-03T10:05:00, TEMP, 35.79}"), Measurement::createMeasurementFromString("{2017-01-03T10:10:00, TEMP, 35.01}")}},
    };

    // Compare the two maps
    ASSERT_EQ(result.size(), expected.size()) << "Result map size: " << result.size() << ", Expected map size: " << expected.size();

    for (const auto& pair : result) {
        auto it = expected.find(pair.first);
        ASSERT_TRUE(it != expected.end()) << "Key not found in expected map: " << pair.first;
        ASSERT_EQ(pair.second.size(), it->second.size()) << "Size mismatch for key: " << pair.first << " (result size: " << pair.second.size() << ", expected size: " << it->second.size() << ")";

        for (size_t i = 0; i < pair.second.size(); ++i) {
            ASSERT_EQ(pair.second[i].toSampledString(), it->second[i].toSampledString()) << "Mismatch in measurements at index " << i << " for type " << pair.first << "\n"
                                                                                          << "Result: " << pair.second[i].toSampledString() << "\n"
                                                                                          << "Expected: " << it->second[i].toSampledString();
        }
    }
}

