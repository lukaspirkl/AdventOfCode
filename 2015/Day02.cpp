#include "pch.h"
#include "aoc.h"
#include <regex>

namespace
{
	int calculateA(std::string input)
	{
		std::regex r("(\\d*)x(\\d*)x(\\d*)");
		std::smatch match;
		int sum = 0;
		while (std::regex_search(input, match, r))
		{
			int l = std::stoi(match[1].str());
			int w = std::stoi(match[2].str());
			int h = std::stoi(match[3].str());
			sum += (2 * l * w) + (2 * w * h) + (2 * h * l) + std::min(std::min(l * w, w * h), h * l);
			input = match.suffix().str();
		}
		return sum;
	}

	TEST(Day02, ExampleA1)
	{
		EXPECT_EQ(calculateA("2x3x4"), 58);
	}

	TEST(Day02, ExampleA2)
	{
		EXPECT_EQ(calculateA("1x1x10"), 43);
	}

	TEST(Day02, InputA)
	{
		std::string input = aoc::readInputFile("Day02.txt").str();
		EXPECT_EQ(calculateA(input), 1588178);
	}

	int calculateB(std::string input)
	{
		std::regex r("(\\d*)x(\\d*)x(\\d*)");
		std::smatch match;
		int sum = 0;
		while (std::regex_search(input, match, r))
		{
			int l = std::stoi(match[1].str());
			int w = std::stoi(match[2].str());
			int h = std::stoi(match[3].str());
			int max = std::max(std::max(l, w), h);
			if (max == h)
			{
				sum += l + l + w + w;
			}
			else if (max == l)
			{
				sum += w + w + h + h;
			}
			else if (max == w)
			{
				sum += h + h + l + l;
			}
			else
			{
				return -1;
			}
			sum += l * w * h;
			input = match.suffix().str();
		}
		return sum;
	}

	TEST(Day02, ExampleB1)
	{
		EXPECT_EQ(calculateB("2x3x4"), 34);
	}

	TEST(Day02, ExampleB2)
	{
		EXPECT_EQ(calculateB("1x1x10"), 14);
	}

	TEST(Day02, InputB)
	{
		std::string input = aoc::readInputFile("Day02.txt").str();
		EXPECT_EQ(calculateB(input), 3783758);
	}
}
