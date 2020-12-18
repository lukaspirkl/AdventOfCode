#include "pch.h"
#include "aoc.h"

#define NAME Day09__Encoding_Error
// https://adventofcode.com/2020/day/9

namespace
{
    std::stringstream GetExampleData()
    {
        std::stringstream ss;
        ss.str(R"(
35
20
15
25
47
40
62
55
65
95
102
117
150
182
127
219
299
277
309
576
)");
        return ss;
    }

    std::vector<unsigned long> Parse(std::stringstream input)
    {
        std::vector<unsigned long> data;
        for (std::string line; std::getline(input, line); ) 
        {
            if (line.size() == 0) continue;
            data.push_back(std::stoll(line));
        }
        return data;
    }

    int FindInvalid(const std::vector<unsigned long>& data, size_t preamble)
    {
        size_t start = 0;

        while(start + preamble < data.size())
        {
            bool found = false;
            int value = data[start + preamble];
            for (size_t i = start; i < start + preamble; i++)
            {
                for (size_t j = i + 1; j < start + preamble; j++)
                {
                    if (data[i] == data[j]) continue;
                    if (data[i] + data[j] == value)
                    {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (!found)
            {
                return value;
            }
            start++;
        }
        return -1;
    }

	TEST(NAME, ExampleA)
	{
        auto data = Parse(GetExampleData());
        int result = FindInvalid(data, 5);
        EXPECT_EQ(result, 127);
	}

    TEST(NAME, InputA)
	{
        auto data = Parse(aoc::readInputFile("Day09.txt"));
        int result = FindInvalid(data, 25);
        EXPECT_EQ(result, 144381670);
	}

    int FindSet(const std::vector<unsigned long>& data, unsigned long num)
    {
        for (size_t i = 0; i < data.size(); i++)
        {
            unsigned long sum = data[i];
            unsigned long min = data[i];
            unsigned long max = data[i];
            for (size_t j = i + 1; j < data.size(); j++)
            {
                sum += data[j];
                min = std::min(min, data[j]);
                max = std::max(max, data[j]);
                if (sum > num) break;
                if (sum == num) return min + max;
            }
        }
        return -1;
    }

    TEST(NAME, ExampleB)
	{
        auto data = Parse(GetExampleData());
        int result = FindSet(data, 127);
        EXPECT_EQ(result, 62);
	}

    TEST(NAME, InputB)
	{
        auto data = Parse(aoc::readInputFile("Day09.txt"));
        int result = FindSet(data, 144381670);
        EXPECT_EQ(result, 20532569);
	}
}
