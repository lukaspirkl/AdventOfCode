#include "pch.h"
#include "aoc.h"

#define NAME Day06__Custom_Customs
// https://adventofcode.com/2020/day/6

namespace
{
	size_t sumAny(std::stringstream input)
	{
		std::unordered_set<char> answers;
		size_t sum = 0;
		for (std::string line; std::getline(input, line); ) {
			if (line.size() == 0)
			{
				sum += answers.size();
				answers.clear();
			}
			for (size_t i = 0; i < line.size(); i++)
			{
				answers.insert(line[i]);
			}
		}
		sum += answers.size();
		return sum;
	}

	TEST(NAME, InputA)
	{
		EXPECT_EQ(sumAny(aoc::readInputFile("Day06.txt")), 6551);
	}

	size_t sumAll(std::stringstream input)
	{
		std::unordered_set<char> answers;
		size_t sum = 0;
		bool skipToNextGroup = false;
		for (std::string line; std::getline(input, line); ) {
			if (line.size() == 0)
			{
				sum += answers.size();
				answers.clear();
				skipToNextGroup = false;
			}
			if (skipToNextGroup) continue;
			if (answers.size() == 0)
			{
				for (size_t i = 0; i < line.size(); i++)
				{
					answers.insert(line[i]);
				}
			}
			else
			{
				std::unordered_set<char> last(answers);
				answers.clear();
				std::copy_if(line.begin(), line.end(), 
					std::inserter(answers, answers.begin()), 
					[last](const char a){ return last.count(a) > 0;}
				);
				skipToNextGroup = (answers.size() == 0);
			}
		}
		sum += answers.size();
		return sum;
	}

	TEST(NAME, InputB)
	{
		EXPECT_EQ(sumAll(aoc::readInputFile("Day06.txt")), 3358);
	}
}
