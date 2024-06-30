#include <gtest/gtest.h>
#include<iostream>
#include <random>
#include <regex>
#include "HelperFunctions.h"

//Random created valid input data should match the the regular expression

TEST(InputFormatTest, RandomInputFormat) {
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
		ASSERT_TRUE(std::regex_match(randomInput, regularExpression)) << "Test failed: " << randomInput << " did not match the expected data format";
	}
}

TEST(InputFormatTest, FixedInputFormat) {
	std::vector<std::string> inputStrings = {
		"{2024-06-30T00:00:00,SPO2,99.9}",
		"{1970-01-01T00:00:00,HEARTRATE,60}",
		"{1960-01-01T00:00:00,TEMP,36.6}",
		"{2024-02-29T00:00:00,BPM,120}",
		"{2099-12-31T23:59:59,SPO2,99.9}",
	};
	for (const auto& input : inputStrings) {
		std::string regexString = R"(^\{((19|20)\d\d-(0[1-9]|1[012])-([012]\d|3[01])T([01]\d|2[0-3]):([0-5]\d):([0-5]\d)),\w*,(-?)(0|([1-9][0-9]*))(\.[0-9]+)?\}$)";
		std::regex regularExpression{ regexString.c_str() };
		ASSERT_TRUE(std::regex_match(input, regularExpression)) << "Test failed: " << input << " did not match the expected data format";
	}		
}

