#include "pch.h"
#include "aoc.h"
#include <regex>

#define NAME Day03__Toboggan_Trajectory
// https://adventofcode.com/2020/day/3

namespace
{
    std::stringstream GetExampleData()
    {
        std::stringstream ss;
        ss.str(R"(
..##.......
#...#...#..
.#....#..#.
..#.#...#.#
.#...##..#.
..#.##.....
.#.#.#....#
.#........#
#.##...#...
#...##....#
.#..#...#.#)");
        return ss;
    }

    std::vector<std::string> ParseInput(std::stringstream input)
    {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(input, line))
		{
            if (line.size() > 0) lines.push_back(line);
		}
        return lines;
    }

    size_t Count(std::vector<std::string> lines, int rightIncrement, int downIncrement)
    {
        size_t maxRight = lines[0].size();
        size_t maxDown = lines.size();
        int count = 0;
        int right = 0;
        int down = 0;
        while (down < maxDown)
        {
            if (lines[down][right] == '#') count++;
            right += rightIncrement;
            down += downIncrement;
            right %= maxRight;
        }
        return count;
    }

    TEST(NAME, ExampleA)
	{
	    auto lines = ParseInput(GetExampleData());
		auto count = Count(lines, 3, 1);
		EXPECT_EQ(count, 7);
	}

    size_t CountB(std::vector<std::string> lines)
    {
        return Count(lines, 1, 1) * Count(lines, 3, 1) *
               Count(lines, 5, 1) * Count(lines, 7, 1) * 
               Count(lines, 1, 2);        
    }

	TEST(NAME, InputA)
	{
	    auto lines = ParseInput(aoc::readInputFile("Day03.txt"));
		auto count = Count(lines, 3, 1);
		EXPECT_EQ(count, 169);
	}

	TEST(NAME, ExampleB)
	{
	    auto lines = ParseInput(GetExampleData());
		auto count = CountB(lines);
		EXPECT_EQ(count, 336);
	}

    TEST(NAME, InputB)
	{
	    auto lines = ParseInput(aoc::readInputFile("Day03.txt"));
		auto count = CountB(lines);
		EXPECT_EQ(count, 7560370818);
	}
}
;