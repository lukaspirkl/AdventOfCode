#include "pch.h"
#include "aoc.h"

#define NAME Day12__Rain_Risk
// https://adventofcode.com/2020/day/12

namespace
{
    std::stringstream GetExampleData()
    {
        std::stringstream ss;
        ss.str(R"(
F10
N3
F7
R90
F11
)");
        return ss;
    }

    long mod(long a, long b)
    {
        return (a%b+b)%b;
    }

    unsigned long CalculateTotalDistanceA(std::stringstream input)
    {
        std::unordered_map<char, int> dirToInt = { {'N', 0 }, {'E', 1 }, {'S', 2 }, {'W', 3 }};
        std::unordered_map<int, char> intToDir = { { 0, 'N'}, { 1, 'E'}, { 2, 'S'}, { 3, 'W'}};

        long east = 0;
        long north = 0;
        char currentDirection = 'E';
		for (std::string line; std::getline(input, line); ) {
            if (line.size() == 0) continue;
			char ch = line[0];
            long distance = std::stoi(line.substr(1, std::string::npos));
            switch (ch)
            {
                case 'F':
                    ch = currentDirection;
                    break;
                case 'L':
                    {
                        int d = dirToInt[currentDirection] - (distance / 90);
                        currentDirection = intToDir[mod(d, 4)];
                    }
                    break;
                case 'R':
                    {
                        int d = dirToInt[currentDirection] + (distance / 90);
                        currentDirection = intToDir[mod(d, 4)];
                    }
                    break;
                default:
                    break;
            }
            switch (ch)
            {
            case 'N':
                north += distance;
                break;
            case 'S':
                north -= distance;
                break;
            case 'E':
                east += distance;
                break;
            case 'W':
                east -= distance;
                break;
            default:
                break;
            }
		}

        return std::abs(east) + std::abs(north);
    }

	TEST(NAME, ExampleA)
	{
        auto distance = CalculateTotalDistanceA(GetExampleData());
		EXPECT_EQ(distance, 25);
	}

    TEST(NAME, InputA)
	{
        auto distance = CalculateTotalDistanceA(aoc::readInputFile("Day12.txt"));
        EXPECT_EQ(distance, 582);
	}

    unsigned long CalculateTotalDistanceB(std::stringstream input)
    {
        long waypointEast = 10;
        long waypointNorth = 1;
        long east = 0;
        long north = 0;

		for (std::string line; std::getline(input, line); ) {
            if (line.size() == 0) continue;
			char ch = line[0];
            long distance = std::stoi(line.substr(1, std::string::npos));
            switch (ch)
            {
                case 'F':
                    east += waypointEast * distance;
                    north += waypointNorth * distance;
                    break;
                case 'L':
                    {
                        for (size_t i = 0; i < distance / 90; i++)
                        {
                            long n = waypointNorth;
                            long e = waypointEast;
                            waypointEast = -n;
                            waypointNorth = e;
                        }
                    }
                    break;
                case 'R':
                    {
                        for (size_t i = 0; i < distance / 90; i++)
                        {
                            long n = waypointNorth;
                            long e = waypointEast;
                            waypointEast = n;
                            waypointNorth = -e;
                        }
                    }
                    break;
                default:
                    break;
            }
            switch (ch)
            {
            case 'N':
                waypointNorth += distance;
                break;
            case 'S':
                waypointNorth -= distance;
                break;
            case 'E':
                waypointEast += distance;
                break;
            case 'W':
                waypointEast -= distance;
                break;
            default:
                break;
            }
		}

        return std::abs(east) + std::abs(north);
    }

	TEST(NAME, ExampleB)
	{
        auto distance = CalculateTotalDistanceB(GetExampleData());
		EXPECT_EQ(distance, 286);
	}

    TEST(NAME, InputB)
	{
        auto distance = CalculateTotalDistanceB(aoc::readInputFile("Day12.txt"));
        EXPECT_EQ(distance, 52069);
	}
}
