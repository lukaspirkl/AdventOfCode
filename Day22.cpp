#include "pch.h"
#include "aoc.h"
#include "gmock/gmock.h"
#include <regex>

namespace
{
	typedef std::vector<size_t> deck;

	deck create(size_t n)
	{
		deck d;
		d.reserve(n);
		for (int i = 0; i < n; i++)
		{
			d.push_back(i);
		}
		return d;
	}

	deck dealIntoNewStack(deck& d)
	{
		deck newd(d.size());
		std::reverse_copy(d.begin(), d.end(), newd.begin());
		return newd;
	}

	TEST(Day22, DealIntoNewStack)
	{
		deck d = create(7);
		ASSERT_THAT(dealIntoNewStack(d), testing::ElementsAre(6, 5, 4, 3, 2, 1, 0));
	}

	deck cutN(deck& d, int n)
	{
		deck newd;
		newd.reserve(d.size());
		if (n > 0)
		{
			newd.insert(newd.end(), d.begin() + n, d.end());
			newd.insert(newd.end(), d.begin(), d.begin() + n);
		}
		if (n < 0)
		{
			newd.insert(newd.end(), d.end() + n, d.end());
			newd.insert(newd.end(), d.begin(), d.end() + n);
		}
		if (n == 0)
		{
			throw std::exception("cutN with zero");
		}
		return newd;
	}

	TEST(Day22, cutNPositive)
	{
		deck d= create(7);
		ASSERT_THAT(cutN(d, 3), testing::ElementsAre(3, 4, 5, 6, 0, 1, 2));
	}

	TEST(Day22, cutNNegative)
	{
		deck d=create(7);
		ASSERT_THAT(cutN(d, -3), testing::ElementsAre(4, 5, 6, 0, 1, 2, 3));
	}

	deck dealWithIncrementN(deck& d, int n)
	{
		deck newd(d.size());
		for (size_t i = 0; i < d.size(); i++)
		{
			size_t newi = (i * n) % d.size();
			newd[newi] = d[i];
		}
		return newd;
	}

	TEST(Day22, dealWithIncrementN)
	{
		deck d= create(10);
		ASSERT_THAT(dealWithIncrementN(d, 3), testing::ElementsAre(0, 7, 4, 1, 8, 5, 2, 9, 6, 3));
	}

	std::vector<std::string> split(const std::string& s)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, '\n'))
		{
			if (token.size() != 0)
			{
				tokens.push_back(token);
			}
		}
		return tokens;
	}

	deck shuffle(deck& d, std::vector<std::string>& lines)
	{
		for (auto& line : lines)
		{
			std::smatch match;

			if (std::regex_search(line, match, std::regex(R"(cut ([\-0-9]*))")) && match.size() > 1)
			{
				d = cutN(d, std::stoi(match.str(1)));
				continue;
			}

			if (std::regex_search(line, match, std::regex(R"(deal with increment ([0-9]*))")) && match.size() > 1)
			{
				d = dealWithIncrementN(d, std::stoi(match.str(1)));
				continue;
			}

			d = dealIntoNewStack(d);
		}

		return d;
	}

	deck processInput(const std::string& input, int n)
	{
		auto lines = split(input);
		deck d = create(n);
		return shuffle(d, lines);
	}

	TEST(Day22, ExampleA1)
	{
		std::string input = R"(
deal with increment 7
deal into new stack
deal into new stack)";

		ASSERT_THAT(processInput(input, 10), testing::ElementsAre(0, 3, 6, 9, 2, 5, 8, 1, 4, 7));
	}

	TEST(Day22, ExampleA2)
	{
		std::string input = R"(
cut 6
deal with increment 7
deal into new stack)";

		ASSERT_THAT(processInput(input, 10), testing::ElementsAre(3, 0, 7, 4, 1, 8, 5, 2, 9, 6));
	}

	TEST(Day22, ExampleA3)
	{
		std::string input = R"(
deal with increment 7
deal with increment 9
cut -2)";

		ASSERT_THAT(processInput(input, 10), testing::ElementsAre(6, 3, 0, 7, 4, 1, 8, 5, 2, 9));
	}

	TEST(Day22, ExampleA4)
	{
		std::string input = R"(
deal into new stack
cut -2
deal with increment 7
cut 8
cut -4
deal with increment 7
cut 3
deal with increment 9
deal with increment 3
cut -1)";

		ASSERT_THAT(processInput(input, 10), testing::ElementsAre(9, 2, 5, 8, 1, 4, 7, 0, 3, 6));
	}

	TEST(Day22, InputA)
	{
		auto input = aoc::readInputFile("Day22.txt").str();
		deck d = processInput(input, 10007);

		auto it = std::find(d.begin(), d.end(), 2019);
		size_t idx = std::distance(d.begin(), it);

		EXPECT_EQ(idx, 4703);
	}

	TEST(Day22, InputB)
	{
		auto max = std::vector<int>().max_size();

		auto input = aoc::readInputFile("Day22.txt").str();
		
		auto lines = split(input);
		deck d = create(119315717514047);
		for (size_t i = 0; i < 101741582076661; i++)
		{
			d = shuffle(d, lines);
		}

		EXPECT_EQ(d[2020], 0);
	}
}
