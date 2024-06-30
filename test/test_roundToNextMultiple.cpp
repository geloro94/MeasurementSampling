#include <gtest/gtest.h>
#include <random>
#include <iostream>
#include "HelperFunctions.h"

//The next multiple modulo the factor should equal 0 furthermore the difference between the roundedValue and the initialValue should be smaller than the factor.
TEST(RoundToNextMultipleTest, RandomNumber) {
	std::random_device rd; 
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<double> randomDoubleDistribution(-10000, 10000);
	std::uniform_int_distribution<> randomPositiveIntDistribution(1, 100);

	for (int i = 0; i < 100000; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			auto initialValue = randomDoubleDistribution(gen);
			auto multiple = randomPositiveIntDistribution(gen);
			auto roundedValue = HelperFunctions::roundUpToNextMultipleOf(initialValue, multiple);
			ASSERT_TRUE(roundedValue % multiple == 0) << "Test Failed: " << std::to_string(roundedValue) << "modulo" << std::to_string(multiple) << "unequal 0." << std::endl;
			ASSERT_TRUE ((roundedValue - initialValue) < multiple) << "Test Failed: " << std::to_string(roundedValue) << "-" << std::to_string(initialValue) << ">" << std::to_string(multiple) << std::endl;
		}
	}
}

TEST(RoundToNextMultipleTest, FixedNumber) {
	ASSERT_EQ(HelperFunctions::roundUpToNextMultipleOf(0, 5), 0);
	ASSERT_EQ(HelperFunctions::roundUpToNextMultipleOf(1, 5), 5);
	ASSERT_EQ(HelperFunctions::roundUpToNextMultipleOf(2, 5), 5);
	ASSERT_EQ(HelperFunctions::roundUpToNextMultipleOf(3, 5), 5);
	ASSERT_EQ(HelperFunctions::roundUpToNextMultipleOf(4, 5), 5);
	ASSERT_EQ(HelperFunctions::roundUpToNextMultipleOf(5, 5), 5);
	ASSERT_EQ(HelperFunctions::roundUpToNextMultipleOf(6, 5), 10);
}

