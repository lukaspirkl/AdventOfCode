#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <iterator>

namespace aoc
{
	struct Coords
	{
		int x{ 0 };
		int y{ 0 };

		Coords operator=(const Coords& o) const {
			return Coords{ o.x, o.y };
		}

		bool operator<(const Coords& o) const {
			return x < o.x || (x == o.x && y < o.y);
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

	std::stringstream readInputFile(const std::string& fileName);
	std::vector<long long> splitLongLong(const std::string& s);
	std::vector<int> splitInt(const std::string& s);
	std::string join(const std::vector<long long>& data);
}
