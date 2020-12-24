#include "pch.h"
#include "aoc.h"
#include <numeric>
#include "boost/multiprecision/cpp_int.hpp"

#define NAME Day13__Shuttle_Search
// https://adventofcode.com/2020/day/13

namespace
{
    unsigned int CalculateA(unsigned int startTime, std::string input)
    {
        unsigned int minTime = std::numeric_limits<unsigned int>::max();
        int minId = -1;
        std::regex regex("(\\d+)");
        std::smatch match;
        while (std::regex_search(input, match, regex))
        {
            unsigned int current = startTime;
            int num = std::stoi(match[1].str());
            while(current % num != 0)
            {
                current++;
            }
            if (current < minTime)
            {
                minTime = current;
                minId = num;
            }
            
            input = match.suffix().str();
        }

        return (minTime - startTime) * minId;
    }

	TEST(NAME, ExampleA)
	{
        std::string input = "7,13,x,x,59,x,31,19";
        auto result = CalculateA(939, input);   
        EXPECT_EQ(result, 295);
	}

	TEST(NAME, InputA)
	{
        std::string input = "37,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,587,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,13,19,x,x,x,23,x,x,x,x,x,29,x,733,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,17";
        auto result = CalculateA(1005526, input);   
        EXPECT_EQ(result, 2935);
	}

    // SECOND PART
    // I don't like this fancy math so the solution is taken from following code:
    // https://github.com/blu3r4y/AdventOfLanguages2020/blob/main/src/day13.cpp
    
    namespace mp = boost::multiprecision;

    std::tuple<mp::int128_t, mp::int128_t, mp::int128_t> xgcd(mp::int128_t a, mp::int128_t b)
    {
        // applies the Extended Euclidean Algorithm which
        // returns `(g, x, y)` such that `ax + by = g = gcd(a, b)`
        // (c) https://en.wikibooks.org/wiki/Algorithm_Implementation/Mathematics/Extended_Euclidean_algorithm

        mp::int128_t x0 = 0, x1 = 1, y0 = 1, y1 = 0;
        while (a != 0)
        {
            mp::int128_t a_ = a;
            mp::int128_t q = b / a;

            // this is b % a but will always return the sign of a (like Python does)
            a = ((b % a) + a) % a;
            b = a_;

            mp::int128_t y0_ = y0;
            y0 = y1;
            y1 = y0_ - q * y1;

            mp::int128_t x0_ = x0;
            x0 = x1;
            x1 = x0_ - q * x1;
        }

        return {b, x0, y0};
    }

    mp::int128_t modulo(mp::int128_t x, mp::int128_t m) {
		return (x % m + m) % m;
	}

    mp::int128_t CalculateB(std::string input)
    {
        // get a list of tuples holding the index and bid values
        std::vector<std::pair<mp::int128_t, mp::int128_t>> constraints;

        std::regex regex("([x\\d]+)");
        std::smatch match;
        size_t i = 0;
        while (std::regex_search(input, match, regex))
        {
            if(match[1].str() != "x")
            {
                int bid = std::stoi(match[1].str());
                constraints.push_back({i, bid});
            }
            input = match.suffix().str();
            i++;
        }

        // given two moduli `an = (a1, n1)` and `bn = (a2, n2)` solves the congruence equation
        // of `x = a1 (mod n1)` and `x = a2 (mod n2)` for `x` by the Chinese Remainder Theorem
        // and therefore returns `xn = (x, n1 * n2)`
        // (c) https://en.wikipedia.org/wiki/Chinese_remainder_theorem#Case_of_two_moduli
        auto chinese_remainder_theorem = [](std::pair<mp::int128_t, mp::int128_t> an, std::pair<mp::int128_t, mp::int128_t> bn) {
            mp::int128_t a1 = an.first, n1 = an.second;
            mp::int128_t a2 = bn.first, n2 = bn.second;

            // Bézout's Identity holds if n1 and n2 are co-prime
            // m1*n1 + m2*n2 = 1 = gcd(n1, n2)
            auto gcd_m1_m2 = xgcd(n1, n2);
            mp::int128_t m1 = std::get<1>(gcd_m1_m2);
            mp::int128_t m2 = std::get<2>(gcd_m1_m2);

            // reduce a and b to a new constraint y = x (mod n1*n2)
            mp::int128_t x = (a1 * m2 * n2) + (a2 * m1 * n1);
            mp::int128_t n = n1 * n2;

            return std::make_pair(x % n, n);
        };

        // solve the general case of the Chinese Remainder Theorem via reduction
        // (c) https://en.wikipedia.org/wiki/Chinese_remainder_theorem#Existence_(constructive_proof)
        auto xn = std::accumulate(constraints.begin() + 1, constraints.end(), constraints[0], chinese_remainder_theorem);
        mp::int128_t n = xn.first;
        mp::int128_t mod = xn.second;

        // retrieve the smallest possible integer for the final congruence
        mp::int128_t smallest = mod - modulo(n, mod);
        return smallest;
    }

    TEST(NAME, ExampleB)
	{
        std::string input = "7,13,x,x,59,x,31,19";
        auto result = CalculateB(input);// CalculateB(input);   
        EXPECT_EQ(result, 1068781);
	}

    TEST(NAME, InputB)
	{
        std::string input = "37,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,587,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,13,19,x,x,x,23,x,x,x,x,x,29,x,733,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,17";
        auto result = CalculateB(input);   
        EXPECT_EQ(result, 836024966345345);
	}
}
