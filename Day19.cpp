#include "pch.h"
#include "aoc.h"
#include "intcode.h"

namespace
{
	int compute(std::vector<long long>& input, int x, int y, std::map<aoc::Coords, int>& cache)
	{
		aoc::Coords c{ x,y };
		if (cache.count(c) == 1)
		{
			return cache[c];
		}
		aoc::intcode intcode(input);
		auto result = intcode.run();
		if (result != aoc::intcode::result::inputRequested)
		{
			throw std::exception("First input not requested.");
		}
		intcode.io = x;
		result = intcode.run();
		if (result != aoc::intcode::result::inputRequested)
		{
			throw std::exception("Second input not requested.");
		}
		intcode.io = y;
		result = intcode.run();
		if (result != aoc::intcode::result::outputProvided)
		{
			throw std::exception("Output not provided.");
		}
		cache.insert({ c, (int)intcode.io });
		return (int)intcode.io;
	}

	TEST(Day19, InputA)
	{
		auto input = aoc::splitLongLong(aoc::readInputFile("Day19.txt").str());
		std::map<aoc::Coords, int> cache;

		int count = 0;
		for (int y = 0; y < 50; y++)
		{
			for (int x = 0; x < 50; x++)
			{
				if (compute(input, x, y, cache) == 1)
				{
					count++;
				}
			}
		}

		EXPECT_EQ(count, 179);
	}

	TEST(Day19, InputB)
	{
		auto input = aoc::splitLongLong(aoc::readInputFile("Day19.txt").str());
		std::map<aoc::Coords, int> cache;

		// some guessed numbers to speed up search
		int startx = 450;
		int starty = 450;

		for (int y = starty; y < std::numeric_limits<size_t>::max(); y++)
		{
			bool afterBeam = false;
			for (int x = startx; x < std::numeric_limits<size_t>::max(); x++)
			{
				if (compute(input, x, y+1, cache) == 0)
				{
					startx++;
				}
				if (compute(input, x, y, cache) == 1)
				{
					afterBeam = true;
					bool found = true;
					for (int i = 0; i < 100; i++)
					{
						if (compute(input, x + i, y, cache) == 0)
						{
							found = false;
							break;
						}
						if (compute(input, x, y + i, cache) == 0)
						{
							found = false;
							break;
						}
					}
					if (found)
					{
						EXPECT_EQ((x * 10000) + y, 9760485);
						return;
					}
				}
				else if (afterBeam)
				{
					break;
				}
			}
		}

		FAIL() << "Result not found";
	}
}
