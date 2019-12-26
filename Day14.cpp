#include "pch.h"
#include "aoc.h"
#include <regex>

#define NAME Day14__Space_Stoichiometry

namespace
{
	std::string large1 = R"(
157 ORE => 5 NZVS
165 ORE => 6 DCFZ
44 XJWVT, 5 KHKGT, 1 QDVJ, 29 NZVS, 9 GPVTF, 48 HKGWZ => 1 FUEL
12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ
179 ORE => 7 PSHF
177 ORE => 5 HKGWZ
7 DCFZ, 7 PSHF => 2 XJWVT
165 ORE => 2 GPVTF
3 DCFZ, 7 NZVS, 5 HKGWZ, 10 PSHF => 8 KHKGT)";

	std::string large2 = R"(
2 VPVL, 7 FWMGM, 2 CXFTF, 11 MNCFX => 1 STKFG
17 NVRVD, 3 JNWZP => 8 VPVL
53 STKFG, 6 MNCFX, 46 VJHF, 81 HVMC, 68 CXFTF, 25 GNMV => 1 FUEL
22 VJHF, 37 MNCFX => 5 FWMGM
139 ORE => 4 NVRVD
144 ORE => 7 JNWZP
5 MNCFX, 7 RFSQX, 2 FWMGM, 2 VPVL, 19 CXFTF => 3 HVMC
5 VJHF, 7 MNCFX, 9 VPVL, 37 CXFTF => 6 GNMV
145 ORE => 6 MNCFX
1 NVRVD => 8 CXFTF
1 VJHF, 6 MNCFX => 4 RFSQX
176 ORE => 6 VJHF)";

	std::string large3 = R"(
171 ORE => 8 CNZTR
7 ZLQW, 3 BMBT, 9 XCVML, 26 XMNCP, 1 WPTQ, 2 MZWV, 1 RJRHP => 4 PLWSL
114 ORE => 4 BHXH
14 VRPVC => 6 BMBT
6 BHXH, 18 KTJDG, 12 WPTQ, 7 PLWSL, 31 FHTLT, 37 ZDVW => 1 FUEL
6 WPTQ, 2 BMBT, 8 ZLQW, 18 KTJDG, 1 XMNCP, 6 MZWV, 1 RJRHP => 6 FHTLT
15 XDBXC, 2 LTCX, 1 VRPVC => 6 ZLQW
13 WPTQ, 10 LTCX, 3 RJRHP, 14 XMNCP, 2 MZWV, 1 ZLQW => 1 ZDVW
5 BMBT => 4 WPTQ
189 ORE => 9 KTJDG
1 MZWV, 17 XDBXC, 3 XCVML => 2 XMNCP
12 VRPVC, 27 CNZTR => 2 XDBXC
15 KTJDG, 12 BHXH => 5 XCVML
3 BHXH, 2 VRPVC => 7 MZWV
121 ORE => 7 VRPVC
7 XCVML => 6 RJRHP
5 BHXH, 4 VRPVC => 5 LTCX)";

	struct reactionIn
	{
		std::string name;
		long long amount;
	};

	struct reactionOut
	{
		long long outCount;
		std::vector<reactionIn> in;
	};

	typedef std::map<std::string, reactionOut> reactions;

	void populate(reactions& reactions, std::string& input)
	{
		std::regex r1(R"((.*) => (\d+) ([A-Z]+))");
		std::regex r2(R"((\d+) ([A-Z]+))");
		std::smatch m1;
		std::smatch m2;
		while (std::regex_search(input, m1, r1))
		{
			reactionOut out;
			out.in = std::vector<reactionIn>();
			out.outCount = std::stoi(m1[2]);

			std::string requirements = m1[1].str();
			while (std::regex_search(requirements, m2, r2))
			{
				out.in.push_back(reactionIn{ m2[2].str(), std::stoi(m2[1].str()) });
				requirements = m2.suffix().str();
			}

			reactions.insert({ m1[3].str(), out });
			input = m1.suffix().str();
		}
		reactions.insert({ "ORE", reactionOut{1, std::vector<reactionIn>{ reactionIn{"ORE",1}}} });
	}

	std::map<std::string, long long> requirementsFor(long long amount, std::string name, reactions& r)
	{
		std::map<std::string, long long> requirements;
		for (auto& in : r[name].in)
		{
			if (requirements.count(in.name) == 0)
			{
				requirements.insert({ in.name, in.amount * amount });
			}
			else
			{
				requirements[in.name] += in.amount * amount;
			}
		}
		return requirements;
	}

	void useLeftovers(std::map<std::string, long long>& requirements, std::map<std::string, long long>& leftovers)
	{
		for (std::map<std::string, long long>::iterator it = requirements.begin(); it != requirements.end();)
		{
			long long left = leftovers[it->first];
			long long requiredAmount = it->second;
			if (left > 0)
			{
				if (left - requiredAmount >= 0)
				{
					leftovers[it->first] -= requiredAmount;
					it = requirements.erase(it);
				}
				else
				{
					leftovers[it->first] = 0;
					it->second -= left;
					it++;
				}
			}
			else
			{
				it++;
			}
		}
	}

	std::map<std::string, long long> requirementsFor(std::map<std::string, long long>& requirements, std::map<std::string, long long>& leftovers, reactions& r)
	{
		std::map<std::string, long long> reqs;
		for (auto& requirement : requirements)
		{
			long long leftover = 0;
			long long amount = (requirement.second / r[requirement.first].outCount);
			if (requirement.second % r[requirement.first].outCount != 0)
			{
				amount = (requirement.second / r[requirement.first].outCount) + 1;
				leftover = r[requirement.first].outCount - (requirement.second % r[requirement.first].outCount);
			}

			leftovers[requirement.first] += leftover;

			auto newReqs = requirementsFor(amount, requirement.first, r);
			for (auto& newReq : newReqs)
			{
				if (reqs.count(newReq.first) == 0)
				{
					reqs.insert(newReq);
				}
				else
				{
					reqs[newReq.first] += newReq.second;
				}
			}
		}
		return reqs;
	}

	long long calculateA(reactions& r, long long fuelAmount = 1)
	{
		std::map<std::string, long long> leftovers;
		for (auto& reaction : r)
		{
			leftovers.insert({ reaction.first, 0 });
		}

		auto requirements = requirementsFor(fuelAmount, "FUEL", r);
		while (true)
		{
			useLeftovers(requirements, leftovers);
			requirements = requirementsFor(requirements, leftovers, r);
			if (requirements.size() == 1 && requirements.count("ORE") == 1)
			{
				break;
			}
		}
		return requirements["ORE"];
	}

	TEST(NAME, ExampleA1)
	{
		std::string input = R"(
10 ORE => 10 A
1 ORE => 1 B
7 A, 1 B => 1 C
7 A, 1 C => 1 D
7 A, 1 D => 1 E
7 A, 1 E => 1 FUEL)";

		reactions r;
		populate(r, input);
		EXPECT_EQ(calculateA(r), 31);
	}

	TEST(NAME, ExampleA2)
	{
		std::string input = R"(
9 ORE => 2 A
8 ORE => 3 B
7 ORE => 5 C
3 A, 4 B => 1 AB
5 B, 7 C => 1 BC
4 C, 1 A => 1 CA
2 AB, 3 BC, 4 CA => 1 FUEL)";

		reactions r;
		populate(r, input);
		EXPECT_EQ(calculateA(r), 165);
	}

	TEST(NAME, ExampleA3)
	{
		reactions r;
		populate(r, large1);
		EXPECT_EQ(calculateA(r), 13312);
	}

	TEST(NAME, ExampleA4)
	{
		reactions r;
		populate(r, large2);
		EXPECT_EQ(calculateA(r), 180697);
	}

	TEST(NAME, ExampleA5)
	{
		reactions r;
		populate(r, large3);
		EXPECT_EQ(calculateA(r), 2210736);
	}

	TEST(NAME, InputA)
	{
		reactions r;
		populate(r, aoc::readInputFile("Day14.txt").str());
		EXPECT_EQ(calculateA(r), 378929);
	}

	TEST(NAME, InputB)
	{
		reactions r;
		populate(r, aoc::readInputFile("Day14.txt").str());
		
		//EXPECT_TRUE(calculateA(r, 3445200) > 1000000000000);
		// I manually tried some values to narrow down the possible range to 3445200-3445300
		
		long long i = 0;
		for (i = 3445200; i <= 3445300; i++)
		{
			if (calculateA(r, i) > 1000000000000)
			{
				i--;
				break;
			}
		}

		EXPECT_EQ(i, 3445249);
		
	}
}
