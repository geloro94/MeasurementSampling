#include <random>
#include <iostream>
#include "HelperFunctions.h"

int main()
{
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
			if (roundedValue % multiple != 0)
			{
				std::cout << "Test Failed: " << std::to_string(roundedValue) << "modulo" << std::to_string(multiple) << "unequal 0." << std::endl;
				return -1;
			}
			if ((roundedValue - initialValue) > multiple)
			{
				std::cout << "Test Failed: " << std::to_string(roundedValue) << "-" << std::to_string(initialValue) << ">" << std::to_string(multiple) << std::endl;
			}
		}
	}
	std::cout << "Test passed" << std::endl;
	return 0;
}
