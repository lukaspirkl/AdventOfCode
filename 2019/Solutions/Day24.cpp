#include "pch.h"
#include "aoc.h"
#include <cmath>

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
					sum += pow(2, (y * m[y].size()) + x);
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

	typedef std::vector<map> multimap;

	char getAdjacentBugs(const multimap& m, const size_t& layer, const size_t& x, const size_t& y)
	{
		if (y == 2 && x == 2)
		{
			return 0;
		}

		char adjacentBugs = 0;
		if (y == 0 && x == 0)
		{
			if (m.at(layer + 1)[2][1]) { adjacentBugs++; }
			if (m.at(layer + 1)[1][2]) { adjacentBugs++; }
			if (m.at(layer)[y][x + 1]) { adjacentBugs++; }
			if (m.at(layer)[y + 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (y == 0 && x == 4)
		{
			if (m.at(layer + 1)[1][2]) { adjacentBugs++; }
			if (m.at(layer + 1)[2][3]) { adjacentBugs++; }
			if (m.at(layer)[y][x - 1]) { adjacentBugs++; }
			if (m.at(layer)[y + 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (y == 4 && x == 0)
		{
			if (m.at(layer + 1)[2][1]) { adjacentBugs++; }
			if (m.at(layer + 1)[3][2]) { adjacentBugs++; }
			if (m.at(layer)[y][x + 1]) { adjacentBugs++; }
			if (m.at(layer)[y - 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (y == 4 && x == 4)
		{
			if (m.at(layer + 1)[2][3]) { adjacentBugs++; }
			if (m.at(layer + 1)[3][2]) { adjacentBugs++; }
			if (m.at(layer)[y][x - 1]) { adjacentBugs++; }
			if (m.at(layer)[y - 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (y == 2 && x == 1)
		{
			for (size_t i = 0; i < 5; i++) { if (m.at(layer - 1)[i][0]) { adjacentBugs++; } }
			if (m.at(layer)[y][x - 1]) { adjacentBugs++; }
			if (m.at(layer)[y + 1][x]) { adjacentBugs++; }
			if (m.at(layer)[y - 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (y == 2 && x == 3)
		{
			if (m.at(layer)[y][x + 1]) { adjacentBugs++; }
			for (size_t i = 0; i < 5; i++) { if (m.at(layer - 1)[i][4]) { adjacentBugs++; } }
			if (m.at(layer)[y + 1][x]) { adjacentBugs++; }
			if (m.at(layer)[y - 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (y == 1 && x == 2)
		{
			if (m.at(layer)[y][x + 1]) { adjacentBugs++; }
			if (m.at(layer)[y][x - 1]) { adjacentBugs++; }
			for (size_t i = 0; i < 5; i++) { if (m.at(layer - 1)[0][i]) { adjacentBugs++; } }
			if (m.at(layer)[y - 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (y == 3 && x == 2)
		{
			if (m.at(layer)[y][x + 1]) { adjacentBugs++; }
			if (m.at(layer)[y][x - 1]) { adjacentBugs++; }
			if (m.at(layer)[y + 1][x]) { adjacentBugs++; }
			for (size_t i = 0; i < 5; i++) { if (m.at(layer - 1)[4][i]) { adjacentBugs++; } }
			return adjacentBugs;
		}

		if (x == 0)
		{
			if (m.at(layer + 1)[2][1]) { adjacentBugs++; }
			if (m.at(layer)[y][x + 1]) { adjacentBugs++; }
			if (m.at(layer)[y - 1][x]) { adjacentBugs++; }
			if (m.at(layer)[y + 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (x == 4)
		{
			if (m.at(layer + 1)[2][3]) { adjacentBugs++; }
			if (m.at(layer)[y][x - 1]) { adjacentBugs++; }
			if (m.at(layer)[y - 1][x]) { adjacentBugs++; }
			if (m.at(layer)[y + 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (y == 0)
		{
			if (m.at(layer + 1)[1][2]) { adjacentBugs++; }
			if (m.at(layer)[y][x + 1]) { adjacentBugs++; }
			if (m.at(layer)[y][x - 1]) { adjacentBugs++; }
			if (m.at(layer)[y + 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (y == 4)
		{
			if (m.at(layer + 1)[3][2]) { adjacentBugs++; }
			if (m.at(layer)[y][x + 1]) { adjacentBugs++; }
			if (m.at(layer)[y][x - 1]) { adjacentBugs++; }
			if (m.at(layer)[y - 1][x]) { adjacentBugs++; }
			return adjacentBugs;
		}

		if (m.at(layer)[y][x + 1]) { adjacentBugs++; }
		if (m.at(layer)[y][x - 1]) { adjacentBugs++; }
		if (m.at(layer)[y + 1][x]) { adjacentBugs++; }
		if (m.at(layer)[y - 1][x]) { adjacentBugs++; }

		return adjacentBugs;
	}

	multimap progress(const multimap& m)
	{
		multimap newm = m;
		for (size_t l = 1; l < m.size() - 1; l++) // skip first and last
		{
			for (size_t y = 0; y < m.at(l).size(); y++)
			{
				for (size_t x = 0; x < m.at(l)[y].size(); x++)
				{
					if (m.at(l)[y][x])
					{
						newm.at(l)[y][x] = getAdjacentBugs(m, l, x, y) == 1;
					}
					else
					{
						char bugs = getAdjacentBugs(m, l, x, y);
						newm.at(l)[y][x] = (bugs == 1 || bugs == 2);
					}
				}
			}
		}
		return newm;
	}

	int countBugs(const multimap& m)
	{
		int count = 0;
		for (size_t l = 0; l < m.size(); l++)
		{
			for (size_t y = 0; y < m.at(l).size(); y++)
			{
				for (size_t x = 0; x < m.at(l)[y].size(); x++)
				{
					if (m.at(l)[y][x])
					{
						count++;
					}
				}
			}
		}
		return count;
	}

	std::string inspect(const multimap& m)
	{
		std::stringstream ss;
		for (size_t i = 0; i < m.size(); i++)
		{
			ss << inspect(m.at(i));
			ss << "\n\n";
		}
		return ss.str();
	}

	TEST(NAME, ExampleB)
	{
		std::string input = R"(
....#
#..#.
#..##
..#..
#....)";

		multimap m;
		m.reserve(20);
		for (int i = 0; i < 20; i++)
		{
			if (i == 10)
			{
				m.push_back(create(input));
			}
			else
			{
				m.push_back(map(5, std::vector<bool>(5, false)));
			}
		}

		for (size_t i = 0; i < 10; i++)
		{
			m = progress(m);
		}

		EXPECT_EQ(countBugs(m), 99);
	}

	TEST(NAME, InputB)
	{
		std::string input = R"(
##.#.
.#.##
.#...
#..#.
.##..)";

		multimap m;
		m.reserve(1000);
		for (int i = 0; i < 1000; i++)
		{
			if (i == 500)
			{
				m.push_back(create(input));
			}
			else
			{
				m.push_back(map(5, std::vector<bool>(5, false)));
			}
		}

		for (size_t i = 0; i < 200; i++)
		{
			m = progress(m);
		}

		EXPECT_EQ(countBugs(m), 1921);
	}
}


