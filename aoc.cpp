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


	int getParameter(std::vector<int>& data, size_t current, int param)
	{
		int parameterMode = data[current] / (int)pow(10, param + 2) % 10;
		if (parameterMode == 1)
		{
			return data[current + param + 1];
		}
		else
		{
			return data[data[current + param + 1]];
		}
	}

	void setParameter(std::vector<int>& data, size_t current, int param, int value)
	{
		data[data[current + param + 1]] = value;
	}

	void runIntcode(int input, std::vector<int>& data, std::vector<int>& output = std::vector<int>())
	{	
		size_t current = 0;

		while (data[current] % 100 != 99)
		{
			switch (data[current] % 100)
			{
			case 1:
				setParameter(data, current, 2, getParameter(data, current, 0) + getParameter(data, current, 1));
				current += 4;
				break;
			case 2:
				setParameter(data, current, 2, getParameter(data, current, 0) * getParameter(data, current, 1));
				current += 4;
				break;
			case 3:
				setParameter(data, current, 0, input);
				current += 2;
				break;
			case 4:
				output.push_back(getParameter(data, current, 0));
				current += 2;
				break;
			case 5:
				if (getParameter(data, current, 0) != 0)
				{
					current = getParameter(data, current, 1);
				}
				else
				{
					current += 3;
				}
				break;
			case 6:
				if (getParameter(data, current, 0) == 0)
				{
					current = getParameter(data, current, 1);
				}
				else
				{
					current += 3;
				}
				break;
			case 7:
				if (getParameter(data, current, 0) < getParameter(data, current, 1))
				{
					setParameter(data, current, 2, 1);
				}
				else
				{
					setParameter(data, current, 2, 0);
				}
				current += 4;
				break;
			case 8:
				if (getParameter(data, current, 0) == getParameter(data, current, 1))
				{
					setParameter(data, current, 2, 1);
				}
				else
				{
					setParameter(data, current, 2, 0);
				}
				current += 4;
				break;
			default:
				return;
			}
		}
	}
}
