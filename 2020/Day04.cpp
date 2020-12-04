#include "pch.h"
#include "aoc.h"
#include <regex>

#define NAME Day04__Passport_Processing
// https://adventofcode.com/2020/day/4

namespace
{
std::stringstream GetExampleData()
    {
        std::stringstream ss;
        ss.str(R"(
ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
hcl:#cfa07d byr:1929

hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm

hcl:#cfa07d eyr:2025 pid:166559648
iyr:2011 ecl:brn hgt:59in)");
        return ss;
    }


    std::vector<std::string> ParseInput(std::string s)
    {
        std::vector<std::string> records;
        std::string delimiter = "\n\n";
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            records.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        records.push_back(s);
        return records;
    }

    size_t CountValidA(std::vector<std::string> records)
    {
        size_t validCount = 0;
        std::vector<std::string> fieldValidators = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
        for(auto record : records)
        {   
            bool valid = true;
            for(auto field : fieldValidators)
            {
                if (record.find(field) == std::string::npos)
                {
                    valid = false;
                    break;
                }
            }
            if (valid) validCount++;
        }
        return validCount;
    }

    bool IsNumberInRange(std::string in, int min, int max)
    {
        int y = std::stoi(in);
        return min <= y && y <= max;
    }

    bool IsNumberInRange(std::string in, std::string regex, int min, int max)
    {
        std::regex r(regex);
        std::smatch match;
        if (std::regex_search(in, match, r))
        {
            return IsNumberInRange(match[0].str(), min, max);
        }
        return false;
    }

    bool IsValid(std::string in, std::string regex)
    {
        std::regex r(regex);
        std::smatch match;
        return std::regex_search(in, match, r);
    }

    size_t CountValidB(std::vector<std::string> records)
    {
        std::unordered_map<std::string, std::function<bool(std::string)>> fieldValidators = {
            {"byr", [](std::string in){ return IsNumberInRange(in, 1920, 2002); }},
            {"iyr", [](std::string in){ return IsNumberInRange(in, 2010, 2020); }},
            {"eyr", [](std::string in){ return IsNumberInRange(in, 2020, 2030); }},
            {"hgt", [](std::string in){ return IsNumberInRange(in, "^(\\d+)cm$", 150, 193) || IsNumberInRange(in, "^(\\d+)in$", 59, 76); }},
            {"hcl", [](std::string in){ return IsValid(in, "^#[\\da-f]{6}$"); }},
            {"ecl", [](std::string in){ return IsValid(in, "^(amb|blu|brn|gry|grn|hzl|oth)$"); }},
            {"pid", [](std::string in){ return IsValid(in, "^\\d{9}$"); }}
        };

        size_t validCount = 0;
        for(auto record : records)
        {   
            bool valid = true;
            for(auto field : fieldValidators)
            {
                std::regex r(field.first+":([\\S]+)");
                std::smatch match;
                if (!std::regex_search(record, match, r) || !field.second(match[1].str()))
                {
                    valid = false;
                    break;
                }
            }
            if (valid) validCount++;
        }
        return validCount;
    }

    TEST(NAME, ExampleA)
    {
        auto input = GetExampleData().str();
        auto records = ParseInput(input);
        auto count = CountValidA(records);
        EXPECT_EQ(count, 2);
    }

	TEST(NAME, InputA)
	{
		auto input = aoc::readInputFile("Day04.txt").str();
        auto records = ParseInput(input);
        auto count = CountValidA(records);
        EXPECT_EQ(count, 264);
	}

	TEST(NAME, InputB)
	{
		auto input = aoc::readInputFile("Day04.txt").str();
        auto records = ParseInput(input);
        auto count = CountValidB(records);
        EXPECT_EQ(count, 224);
	}
}
