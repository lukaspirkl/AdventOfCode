#include "pch.h"

//TODO: Reuse this from Day01
static std::stringstream readInputFile(std::string fileName)
{
	std::ifstream t(fileName);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer;
}

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

int calculateA(std::stringstream& input)
{
	std::map<Coords, std::set<int>> data;
	int lineNumber = 0;
	for (std::string line; std::getline(input, line); )
	{
		lineNumber++;
		Coords current;
		for (auto& step : split(line))
		{
			int distance = std::stoi(step.substr(1, step.size() - 1));
			for (size_t i = 0; i < distance; i++)
			{
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
					data.insert({ current, std::set<int>() });
					it = data.find(current);
				}
			
				it->second.insert(lineNumber);
			}
		}
	}

	int min = std::numeric_limits<int>::max();
	for (const auto& pair : data) {
		if (pair.second.size() >= 2)
		{
			min = std::min(min, std::abs(pair.first.x) + std::abs(pair.first.y));
		}
	}

	return min;
}

TEST(Day03, ExampleA1)
{
	const char* input = "R8,U5,L5,D3\nU7,R6,D4,L4";

	std::stringstream s;
	s << input;

	EXPECT_EQ(calculateA(s), 6);
}

TEST(Day03, ExampleA2)
{
	const char* input = "R75,D30,R83,U83,L12,D49,R71,U7,L72\nU62,R66,U55,R34,D71,R55,D58,R83";

	std::stringstream s;
	s << input;

	EXPECT_EQ(calculateA(s), 159);
}

TEST(Day03, ExampleA3)
{
	const char* input = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51\nU98,R91,D20,R16,D67,R40,U7,R15,U6,R7";

	std::stringstream s;
	s << input;

	EXPECT_EQ(calculateA(s), 135);
}

TEST(Day03, InputA)
{
	auto input = readInputFile("Day03.txt");
	
	EXPECT_EQ(calculateA(input), 1084);
}

int calculateB(std::stringstream& input)
{
	std::map<Coords, std::map<int, int>> data;
	int lineNumber = 0;
	for (std::string line; std::getline(input, line); )
	{
		lineNumber++;
		int steps = 0;
		Coords current;
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
			int sum = 0;
			
			for (const auto& pair2 : pair.second) 
			{
				sum += pair2.second;
			}
			min = std::min(min, sum);
		}
	}

	return min;
}

TEST(Day03, ExampleB1)
{
	const char* input = "R8,U5,L5,D3\nU7,R6,D4,L4";

	std::stringstream s;
	s << input;

	EXPECT_EQ(calculateB(s), 30);
}

TEST(Day03, ExampleB2)
{
	const char* input = "R75,D30,R83,U83,L12,D49,R71,U7,L72\nU62,R66,U55,R34,D71,R55,D58,R83";

	std::stringstream s;
	s << input;

	EXPECT_EQ(calculateB(s), 610);
}

TEST(Day03, ExampleB3)
{
	const char* input = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51\nU98,R91,D20,R16,D67,R40,U7,R15,U6,R7";

	std::stringstream s;
	s << input;

	EXPECT_EQ(calculateB(s), 410);
}

TEST(Day03, InputB)
{
	auto input = readInputFile("Day03.txt");

	EXPECT_EQ(calculateB(input), 9240);
}
