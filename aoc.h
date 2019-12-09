#pragma once
#include "pch.h"

namespace aoc
{
	std::stringstream readInputFile(std::string fileName);
	std::vector<long long> splitLongLong(const std::string& s);
	std::vector<int> splitInt(const std::string& s);
	std::string join(std::vector<long long> data);
}
