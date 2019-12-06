#include "pch.h"
#include "aoc.h"
#include <regex>

namespace
{
	void populate(std::string input, std::map<std::string, std::string> &data)
	{
		std::regex r("([a-zA-Z0-9]*)\\)([a-zA-Z0-9]*)");
		std::smatch match;
		while (std::regex_search(input, match, r))
		{
			data.insert(std::pair<std::string, std::string>(match[2].str(), match[1].str()));
			input = match.suffix().str();
		}
	}

	int calculateA(std::string input)
	{
		std::map<std::string, std::string> data;
		populate(input, data);

		int sum = 0;
		for (auto it = data.begin(); it != data.end(); it++)
		{
			int count = 0;
			for (std::string object = it->first; object != "COM"; object = data[object])
			{
				count++;
			}
			sum += count;
		}
		return sum;
	}

	int calculateB(std::string input)
	{
		std::map<std::string, std::string> data;
		populate(input, data);

		std::vector<std::string> you;

		for (std::string object = "YOU"; object != "COM"; object = data[object])
		{
			you.push_back(object);
		}
		
		std::vector<std::string> san;
		for (std::string object = "SAN"; object != "COM"; object = data[object])
		{
			san.push_back(object);
		}

		while (san.back() == you.back())
		{
			san.pop_back();
			you.pop_back();
		}

		return san.size() + you.size() - 2;
	}

	TEST(Day06, ExampleA1)
	{
		std::string input = "COM)B\nB)C\nC)D\nD)E\nE)F\nB)G\nG)H\nD)I\nE)J\nJ)K\nK)L";
		EXPECT_EQ(calculateA(input), 42);
	}

	TEST(Day06, InputA)
	{
		std::string input = aoc::readInputFile("Day06.txt").str();
		EXPECT_EQ(calculateA(input), 292387);
	}

	TEST(Day06, ExampleB1)
	{
		std::string input = "COM)B\nB)C\nC)D\nD)E\nE)F\nB)G\nG)H\nD)I\nE)J\nJ)K\nK)L\nK)YOU\nI)SAN";
		EXPECT_EQ(calculateB(input), 4);
	}

	TEST(Day06, InputB)
	{
		std::string input = aoc::readInputFile("Day06.txt").str();
		EXPECT_EQ(calculateB(input), 433);
	}
}
