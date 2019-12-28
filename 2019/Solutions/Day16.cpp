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

	// 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
	// 1  0 -1  0  1  0 -1  0  1  0 -1  0  1  0 -1  
	// + = 0  4  8 12 ->  +0(+4)
	// - = 2  6 10 14 ->  +2(+4)

	// 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22
	// 0  1  1  0  0 -1 -1  0  0  1  1  0  0 -1 -1  0  0  1  1  0  0 -1 -1
	// + = 1  2  9 10 17 18 ->  +1(+1+7)
	// - = 5  6 13 14 21 22 ->  +5(+1+7)

	// 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
	// 0  0  1  1  1  0  0  0 -1 -1 -1  0  0  0  1  1  1
	// + = 2  3  4 14 15 16 ->  +2(+1+1+10)
	// - = 8  9 10 20 21 22 ->  +8(+1+1+10)

	// 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22
	// 0  0  0  1  1  1  1  0  0  0  0 -1 -1 -1 -1  0  0  0  0  1  1  1  1
	// ->  +3(+1+1+1+13)
	// -> +11(+1+1+1+13)

	// ->  +4(+1+1+1+1+16)
	// -> +14(+1+1+1+1+16)

	// x = 4
	// +[i] ( (+[1])i +[4+i*] )untilend
	


	std::string calculate(std::vector<int> nums, int phases, int offset = 0)
	{
		std::vector<int> pattern{ 0, 1 , 0 , -1 };

		for (size_t phase = 0; phase < phases; phase++)
		{
			size_t x = 4;
			std::vector<int> newNums;
			for (size_t i = 0; i < nums.size(); i++)
			{	
				size_t idx = i;
				int sum = nums[idx];
				if (i == 0)
				{
					if ((idx + x - 2) < nums.size())
					{
						sum -= nums[idx + x - 2];
					}
					while (idx < nums.size())
					{
						idx += x;
						if (idx < nums.size())
						{
							sum += nums[idx];
						}
						if ((idx + x - 2) < nums.size())
						{
							sum -= nums[idx + x - 2];
						}
					}
				}
				else
				{
					if ((idx + x - 3) < nums.size())
					{
						sum -= nums[idx + x - 3];
					}
					while (idx < nums.size())
					{
						for (size_t j = 0; j < i && idx + 1 < nums.size(); j++)
						{
							idx += 1;
							sum += nums[idx];
							if ((idx + x - 3) < nums.size())
							{
								sum -= nums[idx + x - 3];
							}
						}
						idx += x;
						if (idx < nums.size())
						{
							sum += nums[idx];
						}
						if ((idx + x - 3) < nums.size())
						{
							sum -= nums[idx + x - 3];
						}
					}
				}
				x += 3;
				/*
				int sum2 = 0;
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

				for (size_t j = 0; j < nums.size(); j++)
				{
					sum2 += nums[j] * p[j + 1];
				}
				*/
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

	//Original time: 11sec
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
		FAIL() << "Slow as hell and maybe wrong";
		auto nums = getMegaNums(create("03036732577212944063491565474664"));
		EXPECT_EQ(calculate(nums, 100, 303673), "84462026");
	}

	TEST(NAME, ExampleB3)
	{
		FAIL() << "Slow as hell and maybe wrong";
		auto nums = getMegaNums(create("02935109699940807407585447034323"));
		EXPECT_EQ(calculate(nums, 100, 293510), "78725270");
	}

	TEST(NAME, ExampleB4)
	{
		FAIL() << "Slow as hell and maybe wrong";
		auto nums = getMegaNums(create("03081770884921959731165446850517"));
		EXPECT_EQ(calculate(nums, 100, 308177), "53553731");
	}

	TEST(NAME, InputB)
	{
		FAIL() << "Slow as hell and maybe wrong";
		auto nums = getMegaNums(create(aoc::readInputFile("Day16.txt").str()));
		EXPECT_EQ(calculate(nums, 100, 5970221), "");
	}
}
