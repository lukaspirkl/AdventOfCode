#include "pch.h"
#include "aoc.h"
#include "intcode.h"

#define NAME Day13__Care_Package

namespace
{
	int ai(std::vector<std::vector<int>>& screen)
	{
		size_t xball = 0;
		size_t xpaddle = 0;

		for (size_t x = 0; x < screen.size(); x++)
		{
			for (size_t y = 0; y < screen[x].size(); y++)
			{
				if (screen[x][y] == 3) { xpaddle = x; }
				if (screen[x][y] == 4) { xball = x; }
			}
		}
		if (xball == xpaddle) { return 0; }
		else if (xball < xpaddle) { return -1; }
		else { return 1; }
	}

	TEST(NAME, InputA)
	{
		aoc::intcode intcode(aoc::readInputFile("Day13.txt").str());
		std::map<aoc::Coords, int> screen;

		aoc::intcode::result result;
		while (true)
		{
			aoc::Coords c;
			
			result = intcode.run();
			if (result == aoc::intcode::result::programEnded) { break; }
			c.x = (int)intcode.io;
			
			result = intcode.run();
			if (result == aoc::intcode::result::programEnded) { break; }
			c.y = (int)intcode.io;

			result = intcode.run();
			if (result == aoc::intcode::result::programEnded) { break; }
			screen.insert({ c, (int)intcode.io });
		}

		int blockCount = 0;
		for (auto& pair : screen)
		{
			if (pair.second == 2) { blockCount++; }
		}

		EXPECT_EQ(blockCount, 315);
	}

	TEST(NAME, InputB)
	{
		auto input = aoc::splitLongLong(aoc::readInputFile("Day13.txt").str());
		input[0] = 2;
		aoc::intcode intcode(input);
		std::vector<std::vector<int>> screen(45, std::vector<int>(45, 0));
		int score = 0;

		aoc::intcode::result result;
		int readCount = 0;
		int out[3];
		while (true)
		{
			result = intcode.run();
			if (result == aoc::intcode::result::programEnded)
			{
				break;
			}
			if (result == aoc::intcode::result::outputProvided)
			{
				out[readCount] = (int)intcode.io;
				readCount++;
				if (readCount == 3)
				{
					readCount = 0;
					if (out[0] == -1 && out[1] == 0)
					{
						score = out[2];
					}
					else
					{
						screen[out[0]][out[1]] = out[2];
					}
				}
			}
			if (result == aoc::intcode::result::inputRequested)
			{
				intcode.io = ai(screen);
			}
		}		
		EXPECT_EQ(score, 16171);
	}
}
