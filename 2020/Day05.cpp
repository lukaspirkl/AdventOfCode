#include "pch.h"
#include "aoc.h"

#define NAME Day05__Binary_Boarding
// https://adventofcode.com/2020/day/5

namespace
{
	int getId(std::string seat)
	{
		std::string rowBin = seat.substr(0, 7);
		std::replace(rowBin.begin(), rowBin.end(), 'F', '0');
		std::replace(rowBin.begin(), rowBin.end(), 'B', '1');
		int row = std::stoi(rowBin, 0, 2);

		std::string columnBin = seat.substr(7, 3);
		std::replace(columnBin.begin(), columnBin.end(), 'L', '0');
		std::replace(columnBin.begin(), columnBin.end(), 'R', '1');
		int column = std::stoi(columnBin, 0, 2);

		return (row * 8) + column;
	}

    TEST(NAME, ExampleA1)
    {
        EXPECT_EQ(getId("FBFBBFFRLR"), 357);
    }

	TEST(NAME, ExampleA2)
    {
        EXPECT_EQ(getId("BFFFBBFRRR"), 567);
    }

	TEST(NAME, ExampleA3)
    {
        EXPECT_EQ(getId("FFFBBBFRRR"), 119);
    }

	TEST(NAME, ExampleA4)
    {
        EXPECT_EQ(getId("BBFFBBFRLL"), 820);
    }
    
	TEST(NAME, InputA)
	{
		auto input = aoc::readInputFile("Day05.txt");

		int max = 0;
		for (std::string line; std::getline(input, line); ) {
			int id = getId(line);
			max = std::max(max, id);
		}

		EXPECT_EQ(max, 919);
	}
    
	TEST(NAME, InputB)
	{
		auto input = aoc::readInputFile("Day05.txt");

		int max = 0;
		std::unordered_set<int> ids;
		for (std::string line; std::getline(input, line); ) {
			int id = getId(line);
			ids.emplace(id);
			max = std::max(max, id);
		}

		int found = 0;
		for (int i = 0; i < max; i++)
		{
			if (ids.count(i) == 0 && ids.count(i-1) > 0 && ids.count(i+1) > 0)
			{
				found = i;
				break;
			}
		}
		
		EXPECT_EQ(found, 642);
	}
}
