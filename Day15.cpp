#include "pch.h"
#include "aoc.h"
#include "intcode.h"

#define NAME Day15__Oxygen_System

namespace
{
	struct oxygen
	{
		size_t x = 0;
		size_t y = 0;
		size_t distance = 0;
	};

	const int maxx = 50;
	const int maxy = 50;

	void inspect(std::vector<std::vector<int>>& map, int curx, int cury)
	{
		std::stringstream ss;
		for (size_t y = 0; y < maxx; y++)
		{
			if (y != 0) { ss << '\n'; }
			for (size_t x = 0; x < maxy; x++)
			{
				if (x == curx && y == cury)
				{
					ss << 'X';
				}
				else
				{
					ss << map[x][y];
				}
			}
		}
		std::string s = ss.str();
	}

	oxygen explore(std::vector<std::vector<int>>& map, bool exploreFully)
	{
		aoc::intcode intcode(aoc::readInputFile("Day15.txt").str());

		std::vector<int> directionHistory;

		size_t x = maxx / 2;
		size_t y = maxy / 2;
		map[x][y] = 1;

		size_t nextX = x;
		size_t nextY = y;
		int currentDirection = -1;
		bool goingBack = false;
		oxygen foundOxygen;

		bool running = true;
		while (running)
		{
			auto result = intcode.run();
			switch (result)
			{
			case aoc::intcode::result::inputRequested:
				if (map[x][y - 1] == 0)
				{
					currentDirection = 1;
					intcode.io = 1;
					nextY--;
					goingBack = false;
				}
				else if (map[x][y + 1] == 0)
				{
					currentDirection = 2;
					intcode.io = 2;
					nextY++;
					goingBack = false;
				}
				else if (map[x - 1][y] == 0)
				{
					currentDirection = 4;
					intcode.io = 4;
					nextX--;
					goingBack = false;
				}
				else if (map[x + 1][y] == 0)
				{
					currentDirection = 3;
					intcode.io = 3;
					nextX++;
					goingBack = false;
				}
				else
				{
					if (directionHistory.size() == 0)
					{
						// nowhere else to go (fully explored)
						running = false;
						break;
					}

					goingBack = true;
					switch (directionHistory.back())
					{
					case 1:
						currentDirection = 2;
						intcode.io = 2;
						nextY++;
						break;
					case 2:
						currentDirection = 1;
						intcode.io = 1;
						nextY--;
						break;
					case 3:
						currentDirection = 4;
						intcode.io = 4;
						nextX--;
						break;
					case 4:
						currentDirection = 3;
						intcode.io = 3;
						nextX++;
						break;
					default:
						throw std::exception("Wrong direction in history");
						break;
					}
					directionHistory.pop_back();
				}
				break;
			case aoc::intcode::result::outputProvided:
				switch (intcode.io)
				{
				case 0:
					map[nextX][nextY] = 2; // wall
					nextX = x;
					nextY = y;
					break;
				case 2:
					if (!exploreFully)
					{
						running = false;
					}
					foundOxygen.distance = directionHistory.size() + 1;
					foundOxygen.x = nextX;
					foundOxygen.y = nextY;
				case 1:
					map[nextX][nextY] = 1; // walkable
					x = nextX;
					y = nextY;
					if (!goingBack)
					{
						directionHistory.push_back(currentDirection);
					}
					break;

				default:
					throw std::exception("Invalid output from intcode");
					break;
				}
				break;
			case aoc::intcode::result::programEnded:
				running = false;
				break;
			default:
				throw std::exception("Invalid intcode result");
				break;
			}
		}

		return foundOxygen;
	}

	TEST(NAME, InputA)
	{
		std::vector<std::vector<int>> map(maxx, std::vector<int>(maxy, 0));
		EXPECT_EQ(explore(map, false).distance, 252);
	}

	TEST(NAME, InputB)
	{
		std::vector<std::vector<int>> map(maxx, std::vector<int>(maxy, 0));
		oxygen o = explore(map, true);
		map[o.x][o.y] = 9;

		int minutes = 0;
		bool oxygenEverywhere = false;
		while (!oxygenEverywhere)
		{
			oxygenEverywhere = true;
			std::vector<std::vector<int>> newMap = map;
			for (size_t y = 0; y < maxx; y++)
			{
				for (size_t x = 0; x < maxy; x++)
				{
					if (map[x][y] == 9)
					{
						if (map[x + 1][y] == 1)
						{
							newMap[x + 1][y] = 9;
							oxygenEverywhere = false;
						}
						if (map[x - 1][y] == 1)
						{
							newMap[x - 1][y] = 9;
							oxygenEverywhere = false;
						}
						if (map[x][y + 1] == 1)
						{
							newMap[x][y + 1] = 9;
							oxygenEverywhere = false;
						}
						if (map[x][y - 1] == 1)
						{
							newMap[x][y - 1] = 9;
							oxygenEverywhere = false;
						}
					}
				}
			}
			map = newMap;
			if (!oxygenEverywhere)
			{
				minutes++;
			}
		}
		EXPECT_EQ(minutes, 350);
	}
}
