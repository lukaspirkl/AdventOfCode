#include "pch.h"
#include "aoc.h"

namespace
{

	std::vector<int> create(std::string input)
	{
		std::vector<int> nums;
		for (auto& ch : input)
		{
			nums.push_back(ch - '0');
		}
		return nums;
	}

	std::string calculate(std::vector<int> nums, int phases, int offset = 0)
	{
		std::vector<int> pattern{ 0, 1 , 0 , -1 };

		for (size_t phase = 0; phase < phases; phase++)
		{
			std::vector<int> newNums;
			for (size_t i = 0; i < nums.size(); i++)
			{
				std::vector<int> p;
				for (size_t j = 0; true; j++)
				{
					for (size_t k = 0; k <= i; k++)
					{
						p.push_back(pattern[j % pattern.size()]);
						if (p.size() >= nums.size() + 1) { break; }
					}
					if (p.size() >= nums.size() + 1) { break; }
				}

				int sum = 0;
				for (size_t j = 0; j < nums.size(); j++)
				{
					sum += nums[j] * p[j + 1];
				}
				newNums.push_back(std::abs(sum) % 10);
			}
			nums = newNums;
		}

		std::stringstream ss;
		for (size_t i = offset; i < 8; i++)
		{
			ss << nums[i];
		}
		return ss.str();
	}

	TEST(Day16, ExampleA1)
	{
		auto nums = create("12345678");
		EXPECT_EQ(calculate(nums, 4), "01029498");
	}

	TEST(Day16, ExampleA2)
	{
		auto nums = create("80871224585914546619083218645595");
		EXPECT_EQ(calculate(nums, 100), "24176176");
	}

	TEST(Day16, ExampleA3)
	{
		auto nums = create("19617804207202209144916044189917");
		EXPECT_EQ(calculate(nums, 100), "73745418");
	}

	TEST(Day16, ExampleA4)
	{
		auto nums = create("69317163492948606335995924319873");
		EXPECT_EQ(calculate(nums, 100), "52432133");
	}

	TEST(Day16, InputA)
	{
		auto nums = create(aoc::readInputFile("Day16.txt").str());
		EXPECT_EQ(calculate(nums, 100), "44098263");
	}

	std::vector<int> getMegaNums(std::vector<int>& nums)
	{
		std::vector<int> megaNums;
		for (size_t i = 0; i < 10000; i++)
		{
			megaNums.insert(megaNums.end(), nums.begin(), nums.end());
		}
		return megaNums;
	}

	TEST(Day16, ExampleB2)
	{
		FAIL() << "Slow as hell and maybe wrong";
		auto nums = getMegaNums(create("03036732577212944063491565474664"));
		EXPECT_EQ(calculate(nums, 100, 303673), "84462026");
	}

	TEST(Day16, ExampleB3)
	{
		FAIL() << "Slow as hell and maybe wrong";
		auto nums = getMegaNums(create("02935109699940807407585447034323"));
		EXPECT_EQ(calculate(nums, 100, 293510), "78725270");
	}

	TEST(Day16, ExampleB4)
	{
		FAIL() << "Slow as hell and maybe wrong";
		auto nums = getMegaNums(create("03081770884921959731165446850517"));
		EXPECT_EQ(calculate(nums, 100, 308177), "53553731");
	}

	TEST(Day16, InputB)
	{
		FAIL() << "Slow as hell and maybe wrong";
		auto nums = getMegaNums(create(aoc::readInputFile("Day16.txt").str()));
		EXPECT_EQ(calculate(nums, 100, 5970221), "");
	}
}
