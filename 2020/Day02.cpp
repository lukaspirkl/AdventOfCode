#include "pch.h"
#include "aoc.h"
#include <regex>

#define NAME Day02__Password_Philosophy

namespace
{
	TEST(NAME, InputA)
	{
		auto input = aoc::readInputFile("Day02.txt").str();
		
		int correctCount = 0;

		std::regex r("(\\d+)-(\\d+) ([a-z]): ([a-z]+)");
		std::smatch match;
		while (std::regex_search(input, match, r))
		{
			auto min = std::stoi(match[1].str());
			auto max = std::stoi(match[2].str());
			auto letter = match[3].str()[0];
			auto password = match[4].str();
			int letterCount = 0;
			for (char& ch : password)
			{
				if (ch == letter) letterCount++;
			}
			if (min <= letterCount && letterCount <= max) correctCount++;
			input = match.suffix().str();
		}
		EXPECT_EQ(correctCount, 550);
	}

	TEST(NAME, InputB)
	{
		auto input = aoc::readInputFile("Day02.txt").str();

		int correctCount = 0;

		std::regex r("(\\d+)-(\\d+) ([a-z]): ([a-z]+)");
		std::smatch match;
		while (std::regex_search(input, match, r))
		{
			auto a = std::stoi(match[1].str()) - 1;
			auto b = std::stoi(match[2].str()) - 1;
			auto letter = match[3].str()[0];
			auto password = match[4].str();
			
			if ((password[a] == letter && password[b] != letter) || (password[a] != letter && password[b] == letter))
			{
				correctCount++;
			}
			
			input = match.suffix().str();
		}
		EXPECT_EQ(correctCount, 634);
	}


}
