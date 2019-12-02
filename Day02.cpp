#include "pch.h"

std::vector<int> split(const std::string& s)
{
	std::vector<int> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, ','))
	{
		tokens.push_back(std::stoi(token));
	}
	return tokens;
}

std::string join(std::vector<int> data)
{
	std::stringstream result;
	std::copy(data.begin(), data.end(), std::ostream_iterator<int>(result, ","));
	std::string s = result.str();
	s = s.substr(0, s.length() - 1);  // get rid of the trailing space
	return s;
}

void process(std::vector<int> &data)
{
	size_t current = 0;
	while (data[current] != 99)
	{
		switch (data[current])
		{
		case 1:
			data[data[current + 3]] = data[data[current + 1]] + data[data[current + 2]];
			break;
		case 2:
			data[data[current + 3]] = data[data[current + 1]] * data[data[current + 2]];
			break;
		default:
			break;
		}
		current += 4;
	}
}

std::string calculateA(std::string input)
{
	std::vector<int> data = split(input);
	process(data);
	return join(data);
}

int calculateB(int a, int b)
{
	std::vector<int> data = split("1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,10,19,1,19,5,23,1,6,23,27,1,27,5,31,2,31,10,35,2,35,6,39,1,39,5,43,2,43,9,47,1,47,6,51,1,13,51,55,2,9,55,59,1,59,13,63,1,6,63,67,2,67,10,71,1,9,71,75,2,75,6,79,1,79,5,83,1,83,5,87,2,9,87,91,2,9,91,95,1,95,10,99,1,9,99,103,2,103,6,107,2,9,107,111,1,111,5,115,2,6,115,119,1,5,119,123,1,123,2,127,1,127,9,0,99,2,0,14,0");
	data[1] = a;
	data[2] = b;

	process(data);

	return data[0];
}


TEST(Day02, ExampleA1)
{
	EXPECT_EQ(calculateA("1,9,10,3,2,3,11,0,99,30,40,50"), "3500,9,10,70,2,3,11,0,99,30,40,50");
}

TEST(Day02, ExampleA2)
{
	EXPECT_EQ(calculateA("1,0,0,0,99"), "2,0,0,0,99");
}

TEST(Day02, ExampleA3)
{
	EXPECT_EQ(calculateA("2,3,0,3,99"), "2,3,0,6,99");
}

TEST(Day02, ExampleA4)
{
	EXPECT_EQ(calculateA("2,4,4,5,99,0"), "2,4,4,5,99,9801");
}

TEST(Day02, ExampleA5)
{
	EXPECT_EQ(calculateA("1,1,1,4,99,5,6,0,99"), "30,1,1,4,2,5,6,0,99");
}

TEST(Day02, InputA)
{
	EXPECT_EQ(calculateB(12, 2), 3267740);
}

TEST(Day02, InputB)
{
	for (int noun = 0; noun <= 99; noun++)
	{
		for (int verb = 0; verb <= 99; verb++)
		{
			if (calculateB(noun, verb) == 19690720)
			{
				EXPECT_EQ((100 * noun) + verb, 7870);
				return;
			}
		}
	}
	ASSERT_TRUE(false);
}
