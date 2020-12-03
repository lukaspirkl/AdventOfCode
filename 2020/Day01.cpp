#include "pch.h"
#include "aoc.h"

#define NAME Day01__Report_Repair
// https://adventofcode.com/2020/day/1

namespace
{
	TEST(NAME, InputA)
	{
		auto input = aoc::readInputFile("Day01.txt");

		int result = 0;
		std::vector<int> nums;

		for (std::string line; std::getline(input, line); ) {
			nums.push_back(std::stoi(line));
		}

		for (size_t i = 0; i < nums.size(); i++)
		{
			for (size_t j = 0; j < nums.size(); j++)
			{
				if (i == j) continue;
				if (nums[i] + nums[j] == 2020)
				{
					EXPECT_EQ(nums[i] * nums[j], 259716);
					return;
				}
			}
		}
		EXPECT_FALSE(true);
	}

	TEST(NAME, InputB)
	{
		auto input = aoc::readInputFile("Day01.txt");

		int result = 0;
		std::vector<int> nums;

		for (std::string line; std::getline(input, line); ) {
			nums.push_back(std::stoi(line));
		}

		for (size_t i = 0; i < nums.size(); i++)
		{
			for (size_t j = 0; j < nums.size(); j++)
			{
				if (i == j) continue;
				for (size_t k = 0; k < nums.size(); k++)
				{
					if (i == k || j == k) continue;
					if (nums[i] + nums[j] + nums[k] == 2020)
					{
						EXPECT_EQ(nums[i] * nums[j] * nums[k], 120637440);
						return;
					}
				}
			}
		}
		EXPECT_FALSE(true);
	}
}
