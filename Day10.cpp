#include "pch.h"
#include "aoc.h"

#define NAME Day10__Monitoring_Station

namespace
{
	std::string largeOne = R"(
.#..##.###...#######
##.############..##.
.#.######.########.#
.###.#######.####.#.
#####.##.#.##.###.##
..#####..#.#########
####################
#.####....###.#.#.##
##.#################
#####.##.###..####..
..######..##.#######
####.##.####...##..#
.#####..#.######.###
##...#.##########...
#.##########.#######
.####.#.###.###.#.##
....##.##.###..#####
.#.#.###########.###
#.#.#.#####.####.###
###.##.####.##.#..##)";

	std::string input = R"(
#....#.....#...#.#.....#.#..#....#
#..#..##...#......#.....#..###.#.#
#......#.#.#.....##....#.#.....#..
..#.#...#.......#.##..#...........
.##..#...##......##.#.#...........
.....#.#..##...#..##.....#...#.##.
....#.##.##.#....###.#........####
..#....#..####........##.........#
..#...#......#.#..#..#.#.##......#
.............#.#....##.......#...#
.#.#..##.#.#.#.#.......#.....#....
.....##.###..#.....#.#..###.....##
.....#...#.#.#......#.#....##.....
##.#.....#...#....#...#..#....#.#.
..#.............###.#.##....#.#...
..##.#.........#.##.####.........#
##.#...###....#..#...###..##..#..#
.........#.#.....#........#.......
#.......#..#.#.#..##.....#.#.....#
..#....#....#.#.##......#..#.###..
......##.##.##...#...##.#...###...
.#.....#...#........#....#.###....
.#.#.#..#............#..........#.
..##.....#....#....##..#.#.......#
..##.....#.#......................
.#..#...#....#.#.....#.........#..
........#.............#.#.........
#...#.#......#.##....#...#.#.#...#
.#.....#.#.....#.....#.#.##......#
..##....#.....#.....#....#.##..#..
#..###.#.#....#......#...#........
..#......#..#....##...#.#.#...#..#
.#.##.#.#.....#..#..#........##...
....#...##.##.##......#..#..##....)";

	struct Coords
	{
		double x{ 0 };
		double y{ 0 };

		bool operator==(const Coords& o) const
		{
			return x == o.x && y == o.y;
		}

		bool operator<(const Coords& o) const
		{
			const double epsilon = 0.000001;
			bool xless = std::fabs(x - o.x) > epsilon && (x < o.x);
			bool yless = std::fabs(y - o.y) > epsilon && (y < o.y);
			bool xsame = std::fabs(x - o.x) < epsilon;
			return xless || xsame && yless;
		}

		Coords operator-(const Coords& o) const
		{
			return Coords{ x - o.x, y - o.y };
		}

		Coords operator+(const Coords& o) const
		{
			return Coords{ x + o.x, y + o.y };
		}

		Coords operator*(const int i) const
		{
			return Coords{ x * i, y * i };
		}
	};

	Coords normalize(Coords& coords)
	{
		auto length = std::sqrt(coords.x * coords.x + coords.y * coords.y);
		return Coords{ coords.x / length, coords.y / length };
	}

	double calculateAngle(Coords c)
	{
		const double pi = 3.14159265358979323846;
		Coords unit = normalize(c);
		double angleInRadians = std::atan2(unit.y, unit.x);
		double angleInDegrees = (angleInRadians / pi) * 180.0;
		return std::fmod(angleInDegrees + 90 + 360, 360);
	}

	void populate(std::set<Coords>& asteroids, std::stringstream& map)
	{
		int y = 0;
		for (std::string line; std::getline(map, line); )
		{
			if (line.size() == 0)
			{
				continue;
			}

			for (int x = 0; x < line.size(); x++)
			{
				if (line[x] != '.')
				{
					asteroids.insert(Coords{ x * 1.0, y * 1.0 });
				}
			}

			y++;
		}
	}

	void populate(std::set<Coords>& asteroids, const std::string& map)
	{
		std::stringstream ss;
		ss << map;
		populate(asteroids, ss);
	}

	Coords find200th(const Coords& selected, std::set<Coords>& asteroids)
	{
		std::map<double, std::queue<Coords>> angles;
		for (auto& a : asteroids)
		{
			if (a == selected)
			{
				continue;
			}

			double angle = calculateAngle(a - selected);
			if (angles.count(angle) == 0)
			{
				angles.insert({ angle, std::queue<Coords>() });
			}
			angles[angle].push(a);
		}

		int i = 1;
		while (true)
		{
			for (auto& a : angles)
			{
				if (a.second.size() == 0)
				{
					continue;
				}
				if (i == 200)
				{
					return a.second.front();
				}
				a.second.pop();
				i++;
			}
		}
	}

	size_t countVisible(const Coords& selected, std::set<Coords>& asteroids)
	{
		std::set<double> angles;
		for (auto& a : asteroids)
		{
			if (a == selected)
			{
				continue;
			}

			angles.insert(calculateAngle(a - selected));
		}

		return angles.size();
	}

	size_t bestCountVisible(std::set<Coords>& asteroids)
	{
		size_t best = 0;
		Coords coords;
		for (auto& a : asteroids)
		{
			size_t c = countVisible(a, asteroids);
			if (best < c)
			{
				best = c;
				coords = a;
			}
		}
		return best;
	}

	TEST(NAME, AngleUp)
	{
		EXPECT_EQ(calculateAngle(Coords{ 0, -1 }), 0);
	}
	TEST(NAME, AngleRight)
	{
		EXPECT_EQ(calculateAngle(Coords{ 1, 0 }), 90);
	}
	TEST(NAME, AngleDown)
	{
		EXPECT_EQ(calculateAngle(Coords{ 0, 1 }), 180);
	}
	TEST(NAME, AngleLeft)
	{
		EXPECT_EQ(calculateAngle(Coords{ -1, 0 }), 270);
	}

	TEST(NAME, ExampleA0)
	{
		std::string map = R"(
.7..7
.....
67775
....7
...87)";
		std::set<Coords> asteroids;
		populate(asteroids, map);
		EXPECT_EQ(countVisible(Coords{ 1,0 }, asteroids), 7);
		EXPECT_EQ(countVisible(Coords{ 0,2 }, asteroids), 6);
		EXPECT_EQ(countVisible(Coords{ 3,4 }, asteroids), 8);
	}

	TEST(NAME, ExampleA1)
	{
		std::string map = R"(
......#.#.
#..#.#....
..#######.
.#.#.###..
.#..#.....
..#....#.#
#..#....#.
.##.#..###
##...#..#.
.#....####)";
		std::set<Coords> asteroids;
		populate(asteroids, map);
		EXPECT_EQ(bestCountVisible(asteroids), 33);
	}

	TEST(NAME, ExampleA2)
	{
		std::string map = R"(
#.#...#.#.
.###....#.
.#....#...
##.#.#.#.#
....#.#.#.
.##..###.#
..#...##..
..##....##
......#...
.####.###.)";
		std::set<Coords> asteroids;
		populate(asteroids, map);
		EXPECT_EQ(bestCountVisible(asteroids), 35);
	}

	TEST(NAME, ExampleA3)
	{
		std::string map = R"(
.#..#..###
####.###.#
....###.#.
..###.##.#
##.##.#.#.
....###..#
..#.#..#.#
#..#.#.###
.##...##.#
.....#.#..)";
		std::set<Coords> asteroids;
		populate(asteroids, map);
		EXPECT_EQ(bestCountVisible(asteroids), 41);
	}

	TEST(NAME, ExampleA4)
	{
		std::set<Coords> asteroids;
		populate(asteroids, largeOne);
		EXPECT_EQ(bestCountVisible(asteroids), 210);
	}

	TEST(NAME, InputA)
	{
		std::set<Coords> asteroids;
		populate(asteroids, input);
		EXPECT_EQ(bestCountVisible(asteroids), 267);
	}

	TEST(NAME, ExampleB1)
	{
		std::set<Coords> asteroids;
		populate(asteroids, largeOne);
		Coords the200th = find200th(Coords{ 11.0, 13.0 }, asteroids);
		EXPECT_EQ((the200th.x * 100) + the200th.y, 802);
	}

	TEST(NAME, InputB)
	{
		std::set<Coords> asteroids;
		populate(asteroids, input);
		Coords the200th = find200th(Coords{ 26.0, 28.0 }, asteroids);
		EXPECT_EQ((the200th.x * 100) + the200th.y, 1309);
	}
}
