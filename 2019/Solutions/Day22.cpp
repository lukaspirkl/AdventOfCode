#include "pch.h"
#include "aoc.h"
#include "gmock/gmock.h"
#include <regex>
#include "boost/multiprecision/cpp_int.hpp"

#define NAME Day22__Slam_Shuffle

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

	TEST(NAME, DealIntoNewStack)
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

	TEST(NAME, cutNPositive)
	{
		deck d = create(7);
		ASSERT_THAT(cutN(d, 3), testing::ElementsAre(3, 4, 5, 6, 0, 1, 2));
	}

	TEST(NAME, cutNNegative)
	{
		deck d = create(7);
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

	TEST(NAME, dealWithIncrementN)
	{
		deck d = create(10);
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

	TEST(NAME, ExampleA1)
	{
		std::string input = R"(
deal with increment 7
deal into new stack
deal into new stack)";

		ASSERT_THAT(processInput(input, 10), testing::ElementsAre(0, 3, 6, 9, 2, 5, 8, 1, 4, 7));
	}

	TEST(NAME, ExampleA2)
	{
		std::string input = R"(
cut 6
deal with increment 7
deal into new stack)";

		ASSERT_THAT(processInput(input, 10), testing::ElementsAre(3, 0, 7, 4, 1, 8, 5, 2, 9, 6));
	}

	TEST(NAME, ExampleA3)
	{
		std::string input = R"(
deal with increment 7
deal with increment 9
cut -2)";

		ASSERT_THAT(processInput(input, 10), testing::ElementsAre(6, 3, 0, 7, 4, 1, 8, 5, 2, 9));
	}

	TEST(NAME, ExampleA4)
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

	TEST(NAME, InputA)
	{
		auto input = aoc::readInputFile("Day22.txt").str();
		deck d = processInput(input, 10007);

		auto it = std::find(d.begin(), d.end(), 2019);
		size_t idx = std::distance(d.begin(), it);

		EXPECT_EQ(idx, 4703);
	}


	// SECOND PART 
	// Implementation based on this following tutorial as this fancy math is beyond what I want to know. 
	// https://github.com/mebeim/aoc/blob/master/2019/README.md#day-22---slam-shuffle

	namespace mp = boost::multiprecision;

	mp::int256_t modulo(mp::int256_t x, mp::int256_t m) {
		return (x % m + m) % m;
	}

	template <typename T>
	T modpow(T base, T exp, T modulus) {
		base %= modulus;
		T result = 1;
		while (exp > 0) {
			if (exp & 1) result = (result * base) % modulus;
			base = (base * base) % modulus;
			exp >>= 1;
		}
		return result;
	}

	void transform(mp::int256_t& start, mp::int256_t& step, mp::int256_t& size, std::vector<std::string>& lines)
	{
		for (size_t i = 0; i < lines.size(); i++)
		{
			std::smatch match;

			if (std::regex_search(lines[i], match, std::regex(R"(cut ([\-0-9]*))")) && match.size() > 1)
			{
				mp::int256_t n = std::stoi(match.str(1));
				start += n * step;
			}
			else if (std::regex_search(lines[i], match, std::regex(R"(deal with increment ([0-9]*))")) && match.size() > 1)
			{
				mp::int256_t n = std::stoi(match.str(1));
				step *= modpow(n, size - 2, size);
			}
			else
			{
				step *= -1;
				start += step;
			}

			start = modulo(start, size);
			step = modulo(step, size);
		}
	}

	void repeat(mp::int256_t& start, mp::int256_t& step, mp::int256_t& size, mp::int256_t& repetitions)
	{
		mp::int256_t final_step = modpow(step, repetitions, size);
		mp::int256_t final_start = modulo((start * (1 - final_step) * modpow(modulo((1 - step), size), size - 2, size)), size);
		start = final_start;
		step = final_step;
	}

	TEST(NAME, InputB)
	{
		auto input = aoc::readInputFile("Day22.txt").str();
		auto lines = split(input);

		mp::int256_t start = 0;
		mp::int256_t step = 1;
		mp::int256_t size = 119315717514047;
		mp::int256_t repetitions = 101741582076661;

		transform(start, step, size, lines);
		repeat(start, step, size, repetitions);

		EXPECT_EQ(modulo((start + step * 2020), size), 55627600867625);
	}
}
