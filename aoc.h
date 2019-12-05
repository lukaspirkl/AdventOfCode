#pragma once
#include "pch.h"

namespace aoc
{
	std::stringstream readInputFile(std::string fileName);
	std::vector<int> splitInt(const std::string& s);
	void runIntcode(int input, std::vector<int>& data, std::vector<int>& output = std::vector<int>());
}
