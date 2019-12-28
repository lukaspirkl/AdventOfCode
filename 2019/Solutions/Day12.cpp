#include "pch.h"
#include "aoc.h"
#include <regex>
#include <numeric> 

#define NAME Day12__The_N_Body_Problem

namespace
{
	struct Coords
	{
		int x = 0;
		int y = 0;
		int z = 0;
	};

	void process(std::vector<Coords>& c, std::vector<Coords>& v, int steps, std::vector<int>& zeroesx, std::vector<int>& zeroesy, std::vector<int>& zeroesz)
	{
		for (int i = 0; i < steps; i++)
		{
			for (size_t j = 0; j < c.size(); j++)
			{
				for (size_t k = 0; k < c.size(); k++)
				{
					if (j == k) { continue; }
					if (c[j].x < c[k].x) { v[j].x++; }
					if (c[j].x > c[k].x) { v[j].x--; }
					if (c[j].y < c[k].y) { v[j].y++; }
					if (c[j].y > c[k].y) { v[j].y--; }
					if (c[j].z < c[k].z) { v[j].z++; }
					if (c[j].z > c[k].z) { v[j].z--; }
				}
			}

			for (size_t j = 0; j < c.size(); j++)
			{
				c[j].x += v[j].x;
				c[j].y += v[j].y;
				c[j].z += v[j].z;
			}

			if (v[0].x == 0 && v[1].x == 0 && v[2].x == 0 && v[3].x == 0)
			{
				zeroesx.push_back(i+1);
			}

			if (v[0].y == 0 && v[1].y == 0 && v[2].y == 0 && v[3].y == 0)
			{
				zeroesy.push_back(i+1);
			}

			if (v[0].z == 0 && v[1].z == 0 && v[2].z == 0 && v[3].z == 0)
			{
				zeroesz.push_back(i+1);
			}
		}
	}

	void populate(std::string& input, std::vector<Coords>& c)
	{
		std::regex r(R"(<x=(-?\d*), y=(-?\d*), z=(-?\d*)>)");
		std::smatch match;
		while (std::regex_search(input, match, r))
		{
			Coords co = Coords{ std::stoi(match[1].str()), std::stoi(match[2].str()), std::stoi(match[3].str()) };
			c.push_back(co);
			input = match.suffix().str();
		}
	}

	TEST(NAME, InputA)
	{
		std::string input = R"(
<x=-19, y=-4, z=2>
<x=-9, y=8, z=-16>
<x=-4, y=5, z=-11>
<x=1, y=9, z=-13>)";

		std::vector<Coords> c;
		populate(input, c);
		std::vector<Coords> v(c.size());
		std::vector<int> z;
		process(c, v, 1000, z, z, z);

		int sum = 0;
		for (size_t j = 0; j < c.size(); j++)
		{
			int pot = std::abs(c[j].x) + std::abs(c[j].y) + std::abs(c[j].z);
			int kin = std::abs(v[j].x) + std::abs(v[j].y) + std::abs(v[j].z);
			sum += pot * kin;
		}

		EXPECT_EQ(sum, 8287);
	}

	TEST(NAME, InputB)
	{
		std::string input = R"(
<x=-19, y=-4, z=2>
<x=-9, y=8, z=-16>
<x=-4, y=5, z=-11>
<x=1, y=9, z=-13>)";

		std::vector<Coords> c;
		populate(input, c);
		std::vector<Coords> v(c.size());
		std::vector<int> zx;
		std::vector<int> zy;
		std::vector<int> zz;
		process(c, v, 116000, zx, zy, zz);
		
		EXPECT_EQ(std::lcm(std::lcm((size_t)zx[0], (size_t)zy[0]), (size_t)zz[0]) * 2, 528250271633772);
	}
}
