#include "pch.h"

namespace aoc
{
	std::stringstream readInputFile(std::string fileName)
	{
		std::ifstream t(fileName);
		std::stringstream buffer;
		buffer << t.rdbuf();
		return buffer;
	}
}