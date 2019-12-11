#include "pch.h"
#include "aoc.h"
#include "intcode.h"

namespace
{
	std::string expected = R"(
...##.#..#.####.####.#..#.#..#.###..#..#..
....#.#..#.#....#....#.#..#..#.#..#.#..#..
....#.#..#.###..###..##...####.#..#.####..
....#.#..#.#....#....#.#..#..#.###..#..#..
.#..#.#..#.#....#....#.#..#..#.#....#..#..
..##...##..#....####.#..#.#..#.#....#..#..
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................
..........................................)";

	void populatePlates(int initialColor, std::map<aoc::Coords, int>& plates)
	{
		std::vector<aoc::Coords> directions;
		directions.push_back(aoc::Coords{ 0,-1 });
		directions.push_back(aoc::Coords{ 1,0 });
		directions.push_back(aoc::Coords{ 0,1 });
		directions.push_back(aoc::Coords{ -1,0 });
		aoc::intcode intcode(aoc::readInputFile("Day11.txt").str());
		aoc::intcode::result result;

		aoc::Coords current{ 0,0 };
		int currentDir = 0;

		plates.insert({ current, initialColor });

		while (true)
		{
			if (plates.count(current) == 0)
			{
				plates.insert({ current, 0 });
			}

			result = intcode.run();
			if (result == aoc::intcode::result::programEnded)
			{
				break;
			}
			intcode.io = plates[current];
			result = intcode.run();
			if (result == aoc::intcode::result::programEnded)
			{
				break;
			}
			plates[current] = (int)intcode.io;
			result = intcode.run();
			if (result == aoc::intcode::result::programEnded)
			{
				break;
			}
			int dir = (int)intcode.io;
			if (dir == 0)
			{
				currentDir--;
			}
			else
			{
				currentDir++;
			}
			currentDir = currentDir % directions.size();
			current.x = current.x + directions[currentDir].x;
			current.y = current.y + directions[currentDir].y;
		};
	}

	TEST(Day11, InputA)
	{
		std::map<aoc::Coords, int> plates;
		populatePlates(0, plates);
		EXPECT_EQ(plates.size(), 1909);
	}
	TEST(Day11, InputB)
	{
		std::map<aoc::Coords, int> plates;
		populatePlates(1, plates);
		
		int maxx = 0;
		int maxy = 0;
		int minx = 0;
		int miny = 0;
		for (auto& p : plates)
		{
			if (maxx < p.first.x)
			{
				maxx = p.first.x;
			}
			if (maxy < p.first.x)
			{
				maxy = p.first.x;
			}
			if (minx > p.first.x)
			{
				minx = p.first.x;
			}
			if (miny > p.first.x)
			{
				miny = p.first.x;
			}
		}

		std::stringstream ss;
		for (int y = miny; y < maxy; y++)
		{
			ss << '\n';
			for (int x = minx; x < maxx; x++)
			{
				int paint = 0;
				auto c = aoc::Coords{ x,y };
				if (plates.count(c) == 1 && plates[c] == 1)
				{
					ss << '#';
				}
				else
				{
					ss << '.';
				}
			}
		}

		EXPECT_EQ(ss.str(), expected); // JUFEKHPH
	}
}
