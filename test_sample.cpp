#include <random>

#include "HelperFunctions.h"
#include "Measurement.h"
#include "MeasurementSampler.h"

//The sampled measurement should have vectors of only the given key type of the sampled map.
//All values should be after the starting time-point
//All values should be sorted chronological
//Only one value should be sampled per Interval

int main()
{
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
			for(auto msrmt : randomUnsampledMeasurements)
			{
				if (msrmt.getMeasurmentTime() > randomstartTimepoint)
				{
					std::cout << "Test Failed: " << "Measurements where not sampled" << std::endl;
					return -1;
				}
			}
		}
		
		for (auto& value : sampledMeasurements)
		{
			Instant lastsampledTimePoint{};
			for (auto& msrmt : value.second)
			{
				//Check vector for each type
				if (msrmt.getMeasurementType() != value.first)
				{
					std::cout << "Test Failed: " << "Sampled Value in the Wrong column: " << msrmt.toSampledString() << std::endl;
					return - 1;
				}
				//Check all values before startPoint are ignored
				if (msrmt.getMeasurmentTime() < randomstartTimepoint)
				{
					std::cout << "Test Failed: " << "Sampled Value before samplingStartPoint: " << msrmt.toSampledString() << HelperFunctions::convertToTimeString(randomstartTimepoint, USED_TIME_FORMAT) << std::endl;
					return -1;
				}
				//Check every consecutive MeasuremmentTime has to be larger than the last sampled one
				if (msrmt.getMeasurmentTime() <= lastsampledTimePoint)
				{
					std::cout << "Test Failed: " << msrmt.toSampledString() << std::endl;
					return -1;
				}
				if (msrmt.getSampledTime() - lastsampledTimePoint <  std::chrono::duration<int, std::ratio<60>>{5})
				{
					std::cout << "Test Failed: " << msrmt.toSampledString() << std::endl;
					return -1;
				}
				lastsampledTimePoint = msrmt.getSampledTime();
				//std::cout << msrmt.toSampledString() << std::endl;
			}
		}

	}
	std::cout << "Test passed" << std::endl;
}
		
	
