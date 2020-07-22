#include<iostream>
#include <random>
#include <regex>
#include "HelperFunctions.h"

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned long long> randomTimeDistribution(0, 65 * 365 * 24 * 60 * 60);
	std::uniform_int_distribution<> index(0, 3);
	std::uniform_real_distribution<double> randomDoubleDistribution(-10000, 10000);
	std::vector<std::string> msrmtTypes{ "SPO2", "HEARTRATE", "TEMP", "BPM" };

	for (int i = 0; i < 10000; i++)
	{
		std::chrono::system_clock::time_point randomTimepoint{};
		std::chrono::duration<unsigned long long> secondsSinceEpoche{ randomTimeDistribution(gen) };
		randomTimepoint = randomTimepoint + secondsSinceEpoche;

		auto randomInput = "{" + HelperFunctions::convertToTimeString(randomTimepoint, "%Y-%m-%dT%H:%M:%S") + "," + msrmtTypes[index(gen)] + "," + std::to_string(randomDoubleDistribution(gen)) + "}";

		std::string regexString = R"(^\{((19|20)\d\d-(0[1-9]|1[012])-([012]\d|3[01])T([01]\d|2[0-3]):([0-5]\d):([0-5]\d)),\w*,(-?)(0|([1-9][0-9]*))(\.[0-9]+)?\}$)";
		std::regex regularExpression{ regexString.c_str() };
		if (std::regex_match(randomInput, regularExpression))
		{
			continue;
		}
		else
		{
			std::cout << "Test Failed: " << randomInput << std::endl;
			return -1;
		}
	}
	std::cout << "Test Passed" << std::endl;
	return 0;
}
