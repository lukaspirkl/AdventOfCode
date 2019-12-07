#include "pch.h"
#include "aoc.h"

namespace aoc
{
	std::stringstream readInputFile(std::string fileName)
	{
		std::ifstream t(fileName);
		std::stringstream buffer;
		buffer << t.rdbuf();
		return buffer;
	}

	std::vector<int> splitInt(const std::string& s)
	{
		std::vector<int> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, ','))
		{
			tokens.push_back(std::stoi(token));
		}
		return tokens;
	}
}
