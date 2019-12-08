#include "pch.h"
#include "aoc.h"

namespace
{
	TEST(Day08, InputA)
	{
		std::string input = aoc::readInputFile("Day08.txt").str();

		std::vector<std::vector<int>> layers(input.size()/(25*6), std::vector<int>(25*6));

		for (size_t i = 0; i < input.size(); i++)
		{
			int layer = i / (25 * 6);
			int pixel = i % (25 * 6);

			layers[layer][pixel] = (int)input[i] - 48; //ASCII numeric character
		}

		int fewestZeroCount = std::numeric_limits<int>::max();
		int fewestZeroLayer = 0;
		for (size_t i = 0; i < layers.size(); i++)
		{
			int zeroCount = std::count(layers[i].begin(), layers[i].end(), 0);
			if (fewestZeroCount > zeroCount)
			{
				fewestZeroLayer = i;
				fewestZeroCount = zeroCount;
			}
		}

		int oneCount = std::count(layers[fewestZeroLayer].begin(), layers[fewestZeroLayer].end(), 1);
		int twoCount = std::count(layers[fewestZeroLayer].begin(), layers[fewestZeroLayer].end(), 2);

		EXPECT_EQ(oneCount * twoCount, 2250);
	}

	TEST(Day08, InputB)
	{
		std::string input = aoc::readInputFile("Day08.txt").str();

		std::vector<std::vector<int>> layers(input.size() / (25 * 6), std::vector<int>(25 * 6));

		for (size_t i = 0; i < input.size(); i++)
		{
			int layer = i / (25 * 6);
			int pixel = i % (25 * 6);

			layers[layer][pixel] = (int)input[i] - 48; //ASCII numeric character
		}

		std::stringstream ss;
		for (size_t pixel = 0; pixel < 25*6; pixel++)
		{
			if (pixel % 25 == 0)
			{
				ss << '\n';
			}
			for (size_t layer = 0; layer < layers.size(); layer++)
			{
				int color = layers[layer][pixel];
				if (color == 0)
				{
					ss << ' ';
					break;
				}
				else if (color == 1)
				{
					ss << 'X';
					break;
				}
			}
		}

		std::string expected = R"(
XXXX X  X   XX X  X X    
X    X  X    X X  X X    
XXX  XXXX    X X  X X    
X    X  X    X X  X X    
X    X  X X  X X  X X    
X    X  X  XX   XX  XXXX )";

		EXPECT_EQ(ss.str(), expected);
	}
}
