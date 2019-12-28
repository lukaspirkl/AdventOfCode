#include "pch.h"
#include "aoc.h"
#include <regex>

namespace
{
	bool checkA(std::string input)
	{
		std::regex vowels("([aeiou])");
		std::regex twice(R"((\w)\1+)");
		std::regex badStrings("ab|cd|pq|xy");
		
		std::smatch match;
		int count = 0;
		std::string in = std::string(input);
		while (std::regex_search(in, match, vowels))
		{
			count++;
			in = match.suffix().str();
		}
		bool vowelsPresent = count >= 3;

		std::regex_search(input, match, twice);
		bool letterTwice = match.size() >= 2;

		std::regex_search(input, match, badStrings);
		bool nothingBad = match.size() == 0;

		return vowelsPresent && letterTwice && nothingBad;
	}

	TEST(Day05, ExampleA1)
	{
		EXPECT_TRUE(checkA("ugknbfddgicrmopn"));
	}

	TEST(Day05, ExampleA2)
	{
		EXPECT_TRUE(checkA("aaa"));
	}

	TEST(Day05, ExampleA3)
	{
		EXPECT_FALSE(checkA("jchzalrnumimnmhp"));
	}

	TEST(Day05, ExampleA4)
	{
		EXPECT_FALSE(checkA("haegwjzuvuyypxyu"));
	}

	TEST(Day05, ExampleA5)
	{
		EXPECT_FALSE(checkA("dvszwmarrgswjxmb"));
	}

	TEST(Day05, InputA)
	{
		int count = 0;
		auto input = aoc::readInputFile("Day05.txt");
		for (std::string line; std::getline(input, line); ) {
			if (checkA(line))
			{
				count++;
			}
		}
		EXPECT_EQ(count, 236);
	}

	bool checkB(std::string input)
	{
		std::regex pattern(R"((\w{1}).(\1))");
		std::regex twice(R"((\w{2}).*?(\1))");
	
		std::smatch match;
		
		std::regex_search(input, match, twice);
		bool a = match.size() >= 1;

		std::regex_search(input, match, pattern);
		bool b = match.size() >= 1;

		return a && b;
	}

	TEST(Day05, ExampleB1)
	{
		EXPECT_TRUE(checkB("qjhvhtzxzqqjkmpb"));
	}

	TEST(Day05, ExampleB2)
	{
		EXPECT_TRUE(checkB("xxyxx"));
	}

	TEST(Day05, ExampleB3)
	{
		EXPECT_FALSE(checkB("uurcxstgmygtbstg"));
	}

	TEST(Day05, ExampleB4)
	{
		EXPECT_FALSE(checkB("ieodomkazucvgmuy"));
	}

	TEST(Day05, InputB)
	{
		int count = 0;
		auto input = aoc::readInputFile("Day05.txt");
		for (std::string line; std::getline(input, line); ) {
			if (checkB(line))
			{
				count++;
			}
		}
		EXPECT_EQ(count, 51);
	}
}
