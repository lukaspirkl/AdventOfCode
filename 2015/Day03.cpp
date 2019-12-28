#include "pch.h"
#include "aoc.h"

namespace
{
	struct Coords
	{
		int x{ 0 };
		int y{ 0 };

		bool operator=(const Coords& o) const {
			return x == o.x && y == o.y;
		}

		bool operator<(const Coords& o) const {
			return x < o.x || (x == o.x && y < o.y);
		}
	};

	int calcualteA(std::string input)
	{
		std::map<Coords, int> data;
		Coords current;
		data.insert({ current, 1 });
		for (char& c : input)
		{
			if (c == '>')
			{
				current.x++;
			}
			if (c == '<')
			{
				current.x--;
			}
			if (c == '^')
			{
				current.y++;
			}
			if (c == 'v')
			{
				current.y--;
			}

			auto it = data.find(current);
			if (it == data.end())
			{
				data.insert({ current, 0 });
				it = data.find(current);
			}
			it->second++;
		}

		return data.size();
	}

	TEST(Day03, ExampleA1)
	{
		EXPECT_EQ(calcualteA(">"), 2);
	}

	TEST(Day03, ExampleA2)
	{
		EXPECT_EQ(calcualteA("^>v<"), 4);
	}

	TEST(Day03, ExampleA3)
	{
		EXPECT_EQ(calcualteA("^v^v^v^v^v"), 2);
	}

	TEST(Day03, InputA)
	{
		std::string input = aoc::readInputFile("Day03.txt").str();
		EXPECT_EQ(calcualteA(input), 2592);
	}

	int calcualteB(std::string input)
	{
		std::map<Coords, int> data;
		Coords current[2];
		int turn = 0;
		data.insert({ current[0], 2 });
		for (char& c : input)
		{
			if (c == '>')
			{
				current[turn].x++;
			}
			if (c == '<')
			{
				current[turn].x--;
			}
			if (c == '^')
			{
				current[turn].y++;
			}
			if (c == 'v')
			{
				current[turn].y--;
			}

			auto it = data.find(current[turn]);
			if (it == data.end())
			{
				data.insert({ current[turn], 0 });
				it = data.find(current[turn]);
			}
			it->second++;
			if (turn == 1)
			{
				turn = 0;
			}
			else
			{
				turn = 1;
			}
		}

		return data.size();
	}

	TEST(Day03, ExampleB1)
	{
		EXPECT_EQ(calcualteB("^v"), 3);
	}

	TEST(Day03, ExampleB2)
	{
		EXPECT_EQ(calcualteB("^>v<"), 3);
	}

	TEST(Day03, ExampleB3)
	{
		EXPECT_EQ(calcualteB("^v^v^v^v^v"), 11);
	}

	TEST(Day03, InputB)
	{
		std::string input = aoc::readInputFile("Day03.txt").str();
		EXPECT_EQ(calcualteB(input), 2360);
	}
}
