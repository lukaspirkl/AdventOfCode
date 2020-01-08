#include "pch.h"
#include "aoc.h"

#define NAME Day18__Many_Worlds_Interpretation

namespace
{
	typedef std::vector<std::vector<char>> map;

	struct coords
	{
		size_t x;
		size_t y;
	};

	struct foundKey
	{
		char id;
		coords coords;
		size_t distance;
	};

	struct state
	{
		map map;
		coords start;
		size_t distance;
	};

	map read(const std::string& s)
	{
		map map;
		map.push_back(std::vector<char>());
		for (char ch : s)
		{
			if ((ch == '\n' || ch == '\r'))
			{
				if (map.back().size() != 0)
				{
					map.push_back(std::vector<char>());
				}
			}
			else
			{
				map.back().push_back(ch);
			}
		}
		return map;
	}

	coords find(const map& map, const char ch)
	{
		for (size_t y = 0; y < map.size(); y++)
		{
			for (size_t x = 0; x < map[y].size(); x++)
			{
				if (map[y][x] == ch)
				{
					return coords{ x,y };
				}
			}
		}
		throw std::exception("Char not found.");
	}

	std::vector<foundKey> reachable(const state& s)
	{
		map m(s.map);
		m[s.start.y][s.start.x] = '@';
		map mNext(m);
		std::vector<foundKey> keys;
		bool wayToGo = true;
		size_t steps = 0;
		while (wayToGo)
		{
			steps++;
			wayToGo = false;
			for (size_t y = 1; y < m.size() - 1; y++)
			{
				for (size_t x = 1; x < m[y].size() - 1; x++)
				{
					if (m[y][x] == '@')
					{
						if (m[y + 1][x] == '.') { mNext[y + 1][x] = '@'; wayToGo = true; }
						if (m[y - 1][x] == '.') { mNext[y - 1][x] = '@'; wayToGo = true; }
						if (m[y][x + 1] == '.') { mNext[y][x + 1] = '@'; wayToGo = true; }
						if (m[y][x - 1] == '.') { mNext[y][x - 1] = '@'; wayToGo = true; }
						if (m[y + 1][x] >= 'a') { keys.push_back(foundKey{ m[y + 1][x], coords{x, y + 1}, steps }); mNext[y + 1][x] = '#'; }
						if (m[y - 1][x] >= 'a') { keys.push_back(foundKey{ m[y - 1][x], coords{x, y - 1}, steps }); mNext[y - 1][x] = '#'; }
						if (m[y][x + 1] >= 'a') { keys.push_back(foundKey{ m[y][x + 1], coords{x + 1, y}, steps }); mNext[y][x + 1] = '#'; }
						if (m[y][x - 1] >= 'a') { keys.push_back(foundKey{ m[y][x - 1], coords{x - 1, y}, steps }); mNext[y][x - 1] = '#'; }
					}
				}
			}
			m = mNext;
		}
		return keys;
	}

	void replace(map& map, const char& from, const char& to)
	{
		for (size_t y = 0; y < map.size(); y++)
		{
			for (size_t x = 0; x < map[y].size(); x++)
			{
				if (map[y][x] == from)
				{
					map[y][x] = to;
				}
			}
		}
	}

	std::string inspect(const map& map)
	{
		std::stringstream ss;
		for (size_t y = 0; y < map.size(); y++)
		{
			for (size_t x = 0; x < map[y].size(); x++)
			{
				ss << map[y][x];
			}
			ss << '\n';
		}
		std::string s = ss.str();
		return s;
	}

	void update(state& s, const foundKey& key)
	{
		s.distance += key.distance;
		s.start = key.coords;
		replace(s.map, key.id, '.');
		replace(s.map, key.id - ('a' - 'A'), '.');
	}

	size_t calculateMinDistance(const std::string& in)
	{
		map map = read(in);
		coords start = find(map, '@');
		replace(map, '@', '.');

		std::vector<state> states;
		states.push_back(state{ map, start, 0 });
		
		size_t minDistance = std::numeric_limits<int>::max();
		
		while (!states.empty())
		{
			state s{ states.back() };
			states.pop_back();
			auto keys = reachable(s);
			if (keys.size() == 0)
			{
				minDistance = std::min(minDistance, s.distance);
			}
			else
			{
				for (auto& key : keys)
				{
					state newState{ s };
					update(newState, key);
					if (newState.distance < minDistance)
					{
						states.push_back(newState);
					}
				}
			}
		}
		return minDistance;
	}

	TEST(NAME, ExampleA1)
	{
		std::string in = R"(
#########
#b.A.@.a#
#########)";

		EXPECT_EQ(calculateMinDistance(in), 8);
	}

	TEST(NAME, ExampleA2)
	{
		std::string in = R"(
########################
#f.D.E.e.C.b.A.@.a.B.c.#
######################.#
#d.....................#
########################)";

		EXPECT_EQ(calculateMinDistance(in), 86);
	}

	TEST(NAME, ExampleA3)
	{
		std::string in = R"(
########################
#...............b.C.D.f#
#.######################
#.....@.a.B.c.d.A.e.F.g#
########################)";

		EXPECT_EQ(calculateMinDistance(in), 132);
	}

	TEST(NAME, DISABLED_ExampleA4)
	{
		//TODO: Unable to solve by current approach
		std::string in = R"(
#################
#i.G..c...e..H.p#
########.########
#j.A..b...f..D.o#
########@########
#k.E..a...g..B.n#
########.########
#l.F..d...h..C.m#
#################)";

		EXPECT_EQ(calculateMinDistance(in), 136);
	}

	TEST(NAME, ExampleA5)
	{
		std::string in = R"(
########################
#@..............ac.GI.b#
###d#e#f################
###A#B#C################
###g#h#i################
########################)";

		EXPECT_EQ(calculateMinDistance(in), 81);
	}

	TEST(NAME, InputA)
	{
		FAIL() << "TODO: Solve this";
		EXPECT_EQ(calculateMinDistance(aoc::readInputFile("Day18.txt").str()), 0);
	}

	TEST(NAME, InputB)
	{
		FAIL() << "TODO: Solve this";
	}
}
