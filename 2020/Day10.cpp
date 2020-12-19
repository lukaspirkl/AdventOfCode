#include "pch.h"
#include "aoc.h"

#define NAME Day10__Adapter_Array
// https://adventofcode.com/2020/day/10

namespace
{
    std::vector<unsigned int> Parse(std::stringstream input)
    {
        std::vector<unsigned int> data;
        for (std::string line; std::getline(input, line); ) 
        {
            if (line.size() == 0) continue;
            data.push_back(std::stoll(line));
        }
        return data;
    }

	TEST(NAME, InputA)
	{
        auto data = Parse(aoc::readInputFile("Day10.txt"));
        std::sort(data.begin(), data.end());
        data.insert(data.begin(), 0);
        data.insert(data.end(), data.back()+3);
        std::unordered_map<unsigned int,unsigned int> diffs;
        for (size_t i = 0; i < data.size() - 1; i++)
        {
            unsigned int diff = data[i+1] - data[i];
            diffs.insert({diff, 0});
            diffs[diff]++;
        }
        unsigned int result = diffs[1] * diffs[3];
		EXPECT_EQ(result, 2343);
	}

    TEST(NAME, InputB)
	{
        auto data = Parse(aoc::readInputFile("Day10.txt"));
        //auto data = Parse(GetExampleData());
        std::sort(data.begin(), data.end());
        data.insert(data.begin(), 0);
        data.insert(data.end(), data.back()+3);
        int oneCount = 0;
        unsigned long long combinations = 1;
        std::unordered_map<unsigned int,unsigned int> diffs;
        for (size_t i = 0; i < data.size() - 1; i++)
        {
            if (data[i+1] - data[i] == 1)
            {
                oneCount++;
            }
            else
            {
                // Values precalculated by hand. Thank God that these values are enough.
                if (oneCount == 2) combinations *= 2;
                if (oneCount == 3) combinations *= 4;
                if (oneCount == 4) combinations *= 7; 
                oneCount = 0;
            }
        }
        EXPECT_EQ(combinations, 31581162962944);
	}
}
