#include "pch.h"
#include "aoc.h"

#define NAME Day07__Handy_Haversacks
// https://adventofcode.com/2020/day/7

namespace
{
	std::stringstream GetExampleData()
    {
        std::stringstream ss;
        ss.str(R"(
light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
)");
        return ss;
    }

	std::stringstream GetExampleData2()
    {
        std::stringstream ss;
        ss.str(R"(
shiny gold bags contain 2 dark red bags.
dark red bags contain 2 dark orange bags.
dark orange bags contain 2 dark yellow bags.
dark yellow bags contain 2 dark green bags.
dark green bags contain 2 dark blue bags.
dark blue bags contain 2 dark violet bags.
dark violet bags contain no other bags.
)");
        return ss;
    }

	typedef std::unordered_map<std::string, std::unordered_map<std::string, int>> data;

	data Parse(std::stringstream input)
	{
		data d;
		for (std::string line; std::getline(input, line); ) {
			std::regex regexLine("^(.*) bags? contain (.*).$");
        	std::smatch matchLine;
			if (!std::regex_search(line, matchLine, regexLine)) continue;
			std::string name = matchLine[1].str();
			std::string content = matchLine[2].str();
			d.emplace(name, std::unordered_map<std::string, int>());

			if (content == "no other bags") continue;
			std::regex regexContent("(\\d*) ([^,\\d]*) bags?");
        	std::smatch matchContent;
			while (std::regex_search(content, matchContent, regexContent))
			{
				int c = std::stoi(matchContent[1]);
				std::string n = matchContent[2].str();
				d[name].emplace(n, c);

				content = matchContent.suffix().str();
			}
		}
		return d;
	}

	std::unordered_set<std::string> SearchParents(std::string name, data d)
	{
		std::unordered_set<std::string> parents;

		for(auto& bag : d)
		{
			for(auto& content : bag.second)
			{
				if (content.first == name)
				{
					parents.emplace(bag.first);
				}
			}
		}

		return parents;
	}

	int CountA(data d)
	{
		auto parents = SearchParents("shiny gold", d);
		
		std::unordered_set<std::string> searchFor(parents);
		std::unordered_set<std::string> searchForNext;
		
		while(searchFor.size() != 0)
		{
			for(auto& name : searchFor)
			{
				auto newParents = SearchParents(name, d);
				for (auto& parentName : newParents)
				{
					parents.emplace(parentName);
					searchForNext.emplace(parentName);
				}
			}
			searchFor = searchForNext;
			searchForNext.clear();
		}

		return parents.size();
	}

	int CountBRecursive(data& d, const std::string& name, int count)
	{
		if (d[name].size() == 0) return count;

		int sum = count;
		for(auto& content : d[name])
		{
			sum += CountBRecursive(d, content.first, count * content.second);
		}
		return sum;
	}

	int CountB(data& d)
	{
		return CountBRecursive(d, "shiny gold", 1) - 1;
	}

	TEST(NAME, ExampleA)
	{
		data d = Parse(GetExampleData());
		int result = CountA(d);
		EXPECT_EQ(result, 4);
	}

	TEST(NAME, InputA)
	{
		data d = Parse(aoc::readInputFile("Day07.txt"));
		int result = CountA(d);
		EXPECT_EQ(result, 246);
	}

	TEST(NAME, ExampleB1)
	{
		data d = Parse(GetExampleData());
		int result = CountB(d);
		EXPECT_EQ(result, 32);
	}

	TEST(NAME, ExampleB2)
	{
		data d = Parse(GetExampleData2());
		int result = CountB(d);
		EXPECT_EQ(result, 126);
	}

	std::stringstream GetExampleData3()
    {
        std::stringstream ss;
        ss.str(R"(
shiny gold bags contain 1 cool cyan bag.
cool cyan bags contain 2 leafy lime bag.
leafy lime bags contain no other bags.
)");
        return ss;
    }


	std::stringstream GetExampleData4()
    {
        std::stringstream ss;
        ss.str(R"(
shiny gold bags contain 1 cool cyan bag, 1 awesome aqua bag.
cool cyan bags contain 1 dusty diamond bag.
awesome aqua bags contain 2 dusty diamond bags.
dusty diamond bags contain 1 leafy lime bag.
leafy lime bags contain no other bags.
)");
        return ss;
    }

	TEST(NAME, ExampleB3)
	{
		data d = Parse(GetExampleData3());
		int result = CountB(d);
		EXPECT_EQ(result, 3);
	}

	TEST(NAME, ExampleB4)
	{
		data d = Parse(GetExampleData4());
		int result = CountB(d);
		EXPECT_EQ(result, 8);
	}

	TEST(NAME, InputB)
	{
		data d = Parse(aoc::readInputFile("Day07.txt"));
		int result = CountB(d);
		EXPECT_EQ(result, 2976);
	}
}
