#include "pch.h"
#include "aoc.h"

#define NAME Day01__The_Tyranny_of_the_Rocket_Equation

namespace
{
	int calculateA(int input)
	{
		return (input / 3) - 2;
	}

	TEST(NAME, ExampleA1)
	{
		EXPECT_EQ(calculateA(12), 2);
	}

	TEST(NAME, ExampleA2)
	{
		EXPECT_EQ(calculateA(14), 2);
	}

	TEST(NAME, ExampleA3)
	{
		EXPECT_EQ(calculateA(1969), 654);
	}

	TEST(NAME, ExampleA4)
	{
		EXPECT_EQ(calculateA(100756), 33583);
	}

	TEST(NAME, InputA)
	{
		std::stringstream input = aoc::readInputFile("Day01.txt");

		int sum = 0;

		for (std::string line; std::getline(input, line); ) {
			sum += calculateA(std::stoi(line));
		}

		EXPECT_EQ(sum, 3267890);
	}

	int calculateB(int input)
	{
		int fuel = (input / 3) - 2;
		if (fuel >= 0)
		{
			int additional = calculateB(fuel);
			if (additional >= 0)
			{
				fuel += additional;
			}
		}
		return fuel;
	}

	TEST(NAME, ExampleB1)
	{
		EXPECT_EQ(calculateB(14), 2);
	}

	TEST(NAME, ExampleB2)
	{
		EXPECT_EQ(calculateB(1969), 966);
	}

	TEST(NAME, ExampleB3)
	{
		EXPECT_EQ(calculateB(100756), 50346);
	}

	TEST(NAME, InputB)
	{
		std::stringstream input = aoc::readInputFile("Day01.txt");

		int sum = 0;

		for (std::string line; std::getline(input, line); ) {
			sum += calculateB(std::stoi(line));
		}

		EXPECT_EQ(sum, 4898972);
	}
}
