#include "pch.h"
#include "aoc.h"

namespace
{
	int calculateA(int input)
	{
		return (input / 3) - 2;
	}

	TEST(Day01, ExampleA1)
	{
		EXPECT_EQ(calculateA(12), 2);
	}

	TEST(Day01, ExampleA2)
	{
		EXPECT_EQ(calculateA(14), 2);
	}

	TEST(Day01, ExampleA3)
	{
		EXPECT_EQ(calculateA(1969), 654);
	}

	TEST(Day01, ExampleA4)
	{
		EXPECT_EQ(calculateA(100756), 33583);
	}

	TEST(Day01, InputA)
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

	TEST(Day01, ExampleB1)
	{
		EXPECT_EQ(calculateB(14), 2);
	}

	TEST(Day01, ExampleB2)
	{
		EXPECT_EQ(calculateB(1969), 966);
	}

	TEST(Day01, ExampleB3)
	{
		EXPECT_EQ(calculateB(100756), 50346);
	}

	TEST(Day01, InputB)
	{
		std::stringstream input = aoc::readInputFile("Day01.txt");

		int sum = 0;

		for (std::string line; std::getline(input, line); ) {
			sum += calculateB(std::stoi(line));
		}

		EXPECT_EQ(sum, 4898972);
	}
}
