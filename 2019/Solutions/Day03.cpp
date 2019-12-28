#include "pch.h"
#include "aoc.h"

#define NAME Day03__Crossed_Wires

namespace
{
	std::vector<std::string> split(const std::string& s)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, ','))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	int calculate(std::stringstream& input, int func(std::pair<aoc::Coords, std::map<int, int>>))
	{
		std::map<aoc::Coords, std::map<int, int>> data;
		int lineNumber = 0;
		for (std::string line; std::getline(input, line); )
		{
			lineNumber++;
			int steps = 0;
			aoc::Coords current;
			for (auto& step : split(line))
			{
				int distance = std::stoi(step.substr(1, step.size() - 1));
				for (size_t i = 0; i < distance; i++)
				{
					steps++;
					switch (step[0])
					{
					case 'U':
						current.x++;
						break;
					case 'D':
						current.x--;
						break;
					case 'L':
						current.y--;
						break;
					case 'R':
						current.y++;
						break;
					default:
						break;
					}

					auto it = data.find(current);
					if (it == data.end())
					{
						data.insert({ current, std::map<int, int>() });
						it = data.find(current);
					}

					it->second.insert({ lineNumber, steps });
				}
			}
		}

		int min = std::numeric_limits<int>::max();
		for (const auto& pair : data)
		{
			if (pair.second.size() >= 2)
			{
				min = std::min(min, func(pair));
			}
		}

		return min;
	}

	int calculateA(std::stringstream& input)
	{
		return calculate(input, [](std::pair<aoc::Coords, std::map<int, int>> pair) { return std::abs(pair.first.x) + std::abs(pair.first.y); });
	}

	TEST(NAME, ExampleA1)
	{
		const char* input = "R8,U5,L5,D3\nU7,R6,D4,L4";

		std::stringstream s;
		s << input;

		EXPECT_EQ(calculateA(s), 6);
	}

	TEST(NAME, ExampleA2)
	{
		const char* input = "R75,D30,R83,U83,L12,D49,R71,U7,L72\nU62,R66,U55,R34,D71,R55,D58,R83";

		std::stringstream s;
		s << input;

		EXPECT_EQ(calculateA(s), 159);
	}

	TEST(NAME, ExampleA3)
	{
		const char* input = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51\nU98,R91,D20,R16,D67,R40,U7,R15,U6,R7";

		std::stringstream s;
		s << input;

		EXPECT_EQ(calculateA(s), 135);
	}

	TEST(NAME, InputA)
	{
		auto input = aoc::readInputFile("Day03.txt");

		EXPECT_EQ(calculateA(input), 1084);
	}

	int calculateB(std::stringstream& input)
	{
		return calculate(input, [](std::pair<aoc::Coords, std::map<int, int>> pair) { 
			int sum = 0;
			for (const auto& pair2 : pair.second)
			{
				sum += pair2.second;
			}
			return sum;
		});
	}

	TEST(NAME, ExampleB1)
	{
		const char* input = "R8,U5,L5,D3\nU7,R6,D4,L4";

		std::stringstream s;
		s << input;

		EXPECT_EQ(calculateB(s), 30);
	}

	TEST(NAME, ExampleB2)
	{
		const char* input = "R75,D30,R83,U83,L12,D49,R71,U7,L72\nU62,R66,U55,R34,D71,R55,D58,R83";

		std::stringstream s;
		s << input;

		EXPECT_EQ(calculateB(s), 610);
	}

	TEST(NAME, ExampleB3)
	{
		const char* input = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51\nU98,R91,D20,R16,D67,R40,U7,R15,U6,R7";

		std::stringstream s;
		s << input;

		EXPECT_EQ(calculateB(s), 410);
	}

	TEST(NAME, InputB)
	{
		auto input = aoc::readInputFile("Day03.txt");

		EXPECT_EQ(calculateB(input), 9240);
	}
}
