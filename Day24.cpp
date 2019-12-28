#include "pch.h"
#include "aoc.h"

#define NAME Day24__Planet_of_Discord

namespace
{
	typedef std::vector<std::vector<bool>> map;

	map create(const std::string& input)
	{
		map map;
		map.push_back(std::vector<bool>());
		for (char ch : input)
		{
			if ((ch == '\n' || ch == '\r'))
			{
				if (map.back().size() != 0)
				{
					map.push_back(std::vector<bool>());
				}
			}
			else
			{
				map.back().push_back(ch == '#');
			}
		}
		return map;
	}

	std::string inspect(const map& map)
	{
		std::stringstream ss;
		for (size_t y = 0; y < map.size(); y++)
		{
			ss << '\n';
			for (size_t x = 0; x < map[y].size(); x++)
			{
				ss << (map[y][x] ? '#' : '.');
			}
		}
		std::string s = ss.str();
		return s;
	}

	bool get(const map& m, const size_t& x, const size_t& y)
	{
		if (x < 0 || y < 0 || y >= m[0].size() || x >= m.size())
		{
			return false;
		}
		return m[y][x];
	}

	char getAdjacentBugs(const map& m, const size_t& x, const size_t& y)
	{
		char adjacentBugs = 0;
		if (get(m, x + 1, y)) { adjacentBugs++; }
		if (get(m, x - 1, y)) { adjacentBugs++; }
		if (get(m, x, y + 1)) { adjacentBugs++; }
		if (get(m, x, y - 1)) { adjacentBugs++; }
		return adjacentBugs;
	}

	map progress(const map& m)
	{
		map newm = m;
		for (size_t y = 0; y < m.size(); y++)
		{
			for (size_t x = 0; x < m[y].size(); x++)
			{
				if (m[y][x])
				{
					newm[y][x] = getAdjacentBugs(m, x, y) == 1;
				}
				else
				{
					char bugs = getAdjacentBugs(m, x, y);
					newm[y][x] = (bugs == 1 || bugs == 2);
				}
			}
		}
		return newm;
	}

	unsigned long long getBiodiversityRating(const map& m)
	{
		unsigned long long sum = 0;
		for (size_t y = 0; y < m.size(); y++)
		{
			for (size_t x = 0; x < m[y].size(); x++)
			{
				if (m[y][x])
				{
					sum += std::pow(2, (y * m[y].size()) + x);
				}
			}
		}
		return sum;
	}

	TEST(NAME, OneStep)
	{
		std::string input = R"(
....#
#..#.
#..##
..#..
#....)";
		std::string output = R"(
#..#.
####.
###.#
##.##
.##..)";
		EXPECT_EQ(inspect(progress(create(input))), output);
	}

	TEST(NAME, BiodiversityRating)
	{
		std::string input = R"(
.....
.....
.....
#....
.#...)";
		EXPECT_EQ(getBiodiversityRating(create(input)), 2129920);
	}

	TEST(NAME, InputA)
	{
		std::string input = R"(
##.#.
.#.##
.#...
#..#.
.##..)";

		std::set<unsigned long long> divs;
		map m = create(input);
		while (true)
		{
			auto div = getBiodiversityRating(m);
			if (divs.find(div) != divs.end())
			{
				EXPECT_EQ(div, 17321586);
				break;
			}
			divs.insert(div);
			m = progress(m);
		}
	}

	typedef std::map<int, map> multimap;

	multimap multiCreate(const std::string& input)
	{
		return multimap{ { 0, create(input) } };
	}

	
	bool get(const multimap& m, const int& layer, const size_t& x, const size_t& y)
	{
		if (x < 0 || y < 0 || y >= 5 || x >= 5)
		{
			return false;
		}
		if (x == 2 && y == 1)
		{
			return false;
		}
		return m.at(layer)[y][x];
	}

	char getAdjacentBugs(const map& m, const int& layer, const size_t& x, const size_t& y)
	{
		char adjacentBugs = 0;
		if (get(m, x + 1, y)) { adjacentBugs++; }
		if (get(m, x - 1, y)) { adjacentBugs++; }
		if (get(m, x, y + 1)) { adjacentBugs++; }
		if (get(m, x, y - 1)) { adjacentBugs++; }
		return adjacentBugs;
	}
	
}
