#include "pch.h"
#include "aoc.h"

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

    unsigned long long CalculateB(std::string input)
    {
        return 100000000000000;
    }

    TEST(NAME, ExampleB)
	{
        std::string input = "7,13,x,x,59,x,31,19";
        auto result = CalculateB(input);   
        EXPECT_EQ(result, 1068781);
	}
}
