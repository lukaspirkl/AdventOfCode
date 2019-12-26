#include "pch.h"
#include "aoc.h"

#define NAME Day08__Space_Image_Format

namespace
{
	TEST(NAME, InputA)
	{
		std::string input = aoc::readInputFile("Day08.txt").str();

		std::vector<std::vector<int>> layers(input.size()/(25*6), std::vector<int>(25*6));

		for (size_t i = 0; i < input.size(); i++)
		{
			size_t layer = i / (25 * 6);
			size_t pixel = i % (25 * 6);

			layers[layer][pixel] = (int)input[i] - 48; //ASCII numeric character
		}

		size_t fewestZeroCount = std::numeric_limits<size_t>::max();
		size_t fewestZeroLayer = 0;
		for (size_t i = 0; i < layers.size(); i++)
		{
			size_t zeroCount = std::count(layers[i].begin(), layers[i].end(), 0);
			if (fewestZeroCount > zeroCount)
			{
				fewestZeroLayer = i;
				fewestZeroCount = zeroCount;
			}
		}

		size_t oneCount = std::count(layers[fewestZeroLayer].begin(), layers[fewestZeroLayer].end(), 1);
		size_t twoCount = std::count(layers[fewestZeroLayer].begin(), layers[fewestZeroLayer].end(), 2);

		EXPECT_EQ(oneCount * twoCount, 2250);
	}

	TEST(NAME, InputB)
	{
		std::string input = aoc::readInputFile("Day08.txt").str();

		std::vector<std::vector<int>> layers(input.size() / (25 * 6), std::vector<int>(25 * 6));

		for (size_t i = 0; i < input.size(); i++)
		{
			size_t layer = i / (25 * 6);
			size_t pixel = i % (25 * 6);

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
