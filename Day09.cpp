#include "pch.h"
#include "aoc.h"
#include "intcode.h"

namespace
{
	TEST(Day09, ExampleA1)
	{
		std::string input = "109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99";
		aoc::intcode intcode(input);
		std::vector<long long> output;
		intcode.run(0, output);
		EXPECT_EQ(aoc::join(output), input);
	}

	TEST(Day09, ExampleA2)
	{
		aoc::intcode intcode("1102,34915192,34915192,7,4,7,99,0");
		std::vector<long long> output;
		intcode.run(0, output);
		EXPECT_EQ(output[0], 1219070632396864);
	}

	TEST(Day09, ExampleA3)
	{
		aoc::intcode intcode("104,1125899906842624,99");
		std::vector<long long> output;
		intcode.run(0, output);
		EXPECT_EQ(output[0], 1125899906842624);
	}

	TEST(Day09, InputA)
	{
		aoc::intcode intcode(aoc::readInputFile("Day09.txt").str());
		std::vector<long long> output;
		intcode.run(1, output);
		EXPECT_EQ(output[0], 2752191671);
	}

	TEST(Day09, InputB)
	{
		aoc::intcode intcode(aoc::readInputFile("Day09.txt").str());
		std::vector<long long> output;
		intcode.run(2, output);
		EXPECT_EQ(output[0], 87571);
	}
}