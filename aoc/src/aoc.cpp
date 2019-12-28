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

	std::vector<long long> splitLongLong(const std::string& s)
	{
		std::vector<long long> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, ','))
		{
			tokens.push_back(std::stoll(token));
		}
		return tokens;
	}

	std::string join(std::vector<long long> data)
	{
		std::stringstream result;
		std::copy(data.begin(), data.end(), std::ostream_iterator<long long>(result, ","));
		std::string s = result.str();
		s = s.substr(0, s.length() - 1);  // get rid of the trailing space
		return s;
	}
}
