#include "pch.h"
#include "aoc.h"

#define NAME Day11__Seating_System
// https://adventofcode.com/2020/day/11

namespace
{
    std::stringstream GetExampleData()
    {
        std::stringstream ss;
        ss.str(R"(
L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL
)");
        return ss;
    }

    typedef std::vector<std::vector<char>> seats;

    seats Parse(std::stringstream input)
    {
        seats data;
        for (std::string line; std::getline(input, line); ) {
            if (line.size() == 0) continue;
			data.emplace_back(std::vector<char>());
            for (char c : line)
            {
                data.back().push_back(c);
            }
		}
        return data;
    }

    int Occupied(const seats& data, size_t row, size_t column)
    {
        if (row >= 0 && row < data.size() && column >= 0 && column < data[row].size() && data[row][column] == '#') 
        {
            return 1;
        }
        return 0;
    }

    int OccupiedNeghbors(const seats& data, size_t row, size_t column)
    {
        int c = 0;
        c += Occupied(data, row - 1, column - 1);
        c += Occupied(data, row, column - 1);
        c += Occupied(data, row - 1, column);
        c += Occupied(data, row + 1, column + 1);
        c += Occupied(data, row, column + 1);
        c += Occupied(data, row + 1, column);
        c += Occupied(data, row - 1, column + 1);
        c += Occupied(data, row + 1, column - 1);
        return c;
    }

    char CalculateNew(const seats& data, int emptyLimit, size_t row, size_t column, std::function<int(const seats&, size_t, size_t)> occupiedNeghbors)
    {
        if (data[row][column] == 'L' && occupiedNeghbors(data, row, column) == 0)
        {
            return '#';
        }
        if (data[row][column] == '#' && occupiedNeghbors(data, row, column) >= emptyLimit)
        {
            return 'L';
        }
        return data[row][column];
    }

    size_t StabilizeAndCount(seats current, int emptyLimit, std::function<int(const seats&, size_t, size_t)> occupiedNeighbors)
    {
        seats next;
        for (size_t row = 0; row < current.size(); row++)
        {
            next.emplace_back(std::vector<char>());
            for (size_t column = 0; column < current[row].size(); column++)
            {
                next.back().push_back('.');   
            }
        }
        
        bool same = false;
        size_t occupiedCount = 0;
        while(!same)
        {
            occupiedCount = 0;
            same = true;
            for (size_t row = 0; row < current.size(); row++)
            {
                for (size_t column = 0; column < current[row].size(); column++)
                {
                    char newState = CalculateNew(current, emptyLimit, row, column, occupiedNeighbors);
                    if (newState == '#') occupiedCount++;
                    if (newState != next[row][column]) same = false;
                    next[row][column] = newState;
                }
            }
            current = next;
        }
        return occupiedCount;
    }

	TEST(NAME, ExampleA)
	{
        auto current = Parse(GetExampleData());
        size_t count = StabilizeAndCount(current, 4, OccupiedNeghbors);
        EXPECT_EQ(count, 37);	
	}

	TEST(NAME, InputA)
	{
        auto current = Parse(aoc::readInputFile("Day11.txt"));
        size_t count = StabilizeAndCount(current, 4, OccupiedNeghbors);
        EXPECT_EQ(count, 2324);	
	}

    std::stringstream GetBSeat8()
    {
        std::stringstream ss;
        ss.str(R"(
.......#.
...#.....
.#.......
.........
..#L....#
....#....
.........
#........
...#.....
)");
        return ss;
    }

    std::stringstream GetBSeat0()
    {
        std::stringstream ss;
        ss.str(R"(
.##.##.
#.#.#.#
##...##
...L...
##...##
#.#.#.#
.##.##.
)");
        return ss;
    }

    int OccupiedFar(const seats& data, size_t row, size_t column, int rowDiff, int columnDiff)
    {
        while(true)
        {
            row += rowDiff;
            column += columnDiff;
            if (row >= 0 && row < data.size() && column >= 0 && column < data[row].size())
            {
                if (data[row][column] == '#') return 1;
                if (data[row][column] == 'L') return 0;
            }
            else
            {
                return 0;
            }
        }
    }

    int OccupiedFarNeghbors(const seats& data, size_t row, size_t column)
    {
        int c = 0;
        c += OccupiedFar(data, row, column, -1, -1);
        c += OccupiedFar(data, row, column,  0, -1);
        c += OccupiedFar(data, row, column, -1,  0);
        c += OccupiedFar(data, row, column, +1, +1);
        c += OccupiedFar(data, row, column,  0, +1);
        c += OccupiedFar(data, row, column, +1,  0);
        c += OccupiedFar(data, row, column, -1, +1);
        c += OccupiedFar(data, row, column, +1, -1);
        return c;
    }    

	TEST(NAME, ExampleB8)
	{
        auto current = Parse(GetBSeat8());
        int count = OccupiedFarNeghbors(current, 4, 3);
        EXPECT_EQ(count, 8);
	}

    TEST(NAME, ExampleB0)
	{
        auto current = Parse(GetBSeat0());
        int count = OccupiedFarNeghbors(current, 3, 3);
        EXPECT_EQ(count, 0);
	}

    	TEST(NAME, ExampleB)
	{
        auto current = Parse(GetExampleData());
        size_t count = StabilizeAndCount(current, 5, OccupiedFarNeghbors);
        EXPECT_EQ(count, 26);	
	}

    TEST(NAME, InputB)
	{
        auto current = Parse(aoc::readInputFile("Day11.txt"));
        size_t count = StabilizeAndCount(current, 5, OccupiedFarNeghbors);
        EXPECT_EQ(count, 2068);	
	}
}
