#include "pch.h"
#include "aoc.h"

#define NAME Day16__Flawed_Frequency_Transmission

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
		std::vector<int> newNums(nums.size());

		for (size_t phase = 0; phase < phases; phase++)
		{
			for (size_t i = offset; i <= nums.size() / 2; i++)
			{
				int sum = 0;
				for (size_t j = i; j < nums.size(); )
				{
					for (size_t k = j; k < j + i + 1 && k < nums.size(); k++)
					{
						sum += nums[k];
					}
					j += 2 * (i + 1);
					for (size_t k = j; k < j + i + 1 && k < nums.size(); k++)
					{
						sum -= nums[k];
					}
					j += 2 * (i + 1);
				}

				newNums[i] = std::abs(sum) % 10;
			}

			long long sum = 0;
			for (size_t i = nums.size() - 1; i > nums.size() / 2 && i >= offset; i--)
			{
				sum += nums[i];
				newNums[i] = std::abs(sum) % 10;
			}
			nums = newNums;
		}

		std::stringstream ss;
		for (size_t i = offset; i < offset + 8; i++)
		{
			ss << nums[i];
		}
		return ss.str();
	}

	TEST(NAME, ExampleA1)
	{
		auto nums = create("12345678");
		EXPECT_EQ(calculate(nums, 4), "01029498");
	}

	TEST(NAME, ExampleA2)
	{
		auto nums = create("80871224585914546619083218645595");
		EXPECT_EQ(calculate(nums, 100), "24176176");
	}

	TEST(NAME, ExampleA3)
	{
		auto nums = create("19617804207202209144916044189917");
		EXPECT_EQ(calculate(nums, 100), "73745418");
	}

	TEST(NAME, ExampleA4)
	{
		auto nums = create("69317163492948606335995924319873");
		EXPECT_EQ(calculate(nums, 100), "52432133");
	}

	TEST(NAME, InputA)
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

	TEST(NAME, ExampleB2)
	{
		auto n = create("03036732577212944063491565474664");
		auto nums = getMegaNums(n);
		EXPECT_EQ(calculate(nums, 100, 303673), "84462026");
	}

	TEST(NAME, ExampleB3)
	{
		auto n = create("02935109699940807407585447034323");
		auto nums = getMegaNums(n);
		EXPECT_EQ(calculate(nums, 100, 293510), "78725270");
	}

	TEST(NAME, ExampleB4)
	{
		auto n = create("03081770884921959731165446850517");
		auto nums = getMegaNums(n);
		EXPECT_EQ(calculate(nums, 100, 308177), "53553731");
	}

	TEST(NAME, InputB)
	{
		auto n = create(aoc::readInputFile("Day16.txt").str());
		auto nums = getMegaNums(n);
		EXPECT_EQ(calculate(nums, 100, 5970221), "12482168");
	}
}
