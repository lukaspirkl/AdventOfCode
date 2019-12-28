#include "pch.h"
#include "aoc.h"
#include "intcode.h"

#define NAME Day07__Amplification_Circuit

namespace
{
	int findMaxSignal(int getSignal(const std::string& prgString, std::vector<int>& phases), std::string prg, int phaseStart)
	{
		std::vector<int> phases(5);
		std::generate(phases.begin(), phases.end(), [n = phaseStart]() mutable { return n++; });

		int maxSignal = 0;
		do
		{
			int signal = getSignal(prg, phases);
			if (signal > maxSignal)
			{
				maxSignal = signal;
			}
		} while (std::next_permutation(phases.begin(), phases.end()));

		return maxSignal;
	}

	int getSignalA(const std::string& prgString, std::vector<int>& phases)
	{
		auto program = aoc::splitLongLong(prgString);

		int signal = 0;
		for (size_t i = 0; i < phases.size(); i++)
		{
			aoc::intcode amp(program);
			if (amp.run() != aoc::intcode::result::inputRequested)
			{
				return -1;
			}
			amp.io = phases[i];
			if (amp.run() != aoc::intcode::result::inputRequested)
			{
				return -1;
			}
			amp.io = signal;
			if (amp.run() != aoc::intcode::result::outputProvided)
			{
				return -1;
			}
			signal = (int)amp.io;
		}
		return signal;
	}

	int getSignalB(const std::string& prgString, std::vector<int>& phases)
	{
		auto program = aoc::splitLongLong(prgString);

		std::vector<aoc::intcode> amps;
		for (size_t i = 0; i < phases.size(); i++)
		{
			amps.push_back(aoc::intcode(program));
			if (amps.back().run() != aoc::intcode::result::inputRequested)
			{
				return -1;
			}
			amps[i].io = phases[i];
		}

		bool run = true;
		int signal = 0;
		while (run)
		{
			for (auto& amp : amps)
			{
				if (amp.run() != aoc::intcode::result::inputRequested)
				{
					run = false;
					continue;
				}
				amp.io = signal;
				if (amp.run() != aoc::intcode::result::outputProvided)
				{
					run = false;
					continue;
				}
				signal = (int)amp.io;
			}
		}
		return signal;
	}

	TEST(NAME, ExampleA1)
	{
		std::string prg = "3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0";
		EXPECT_EQ(findMaxSignal(getSignalA, prg, 0), 43210);
	}

	TEST(NAME, ExampleA2)
	{
		std::string prg = "3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0";
		EXPECT_EQ(findMaxSignal(getSignalA, prg, 0), 54321);
	}

	TEST(NAME, ExampleA3)
	{
		std::string prg = "3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0";
		EXPECT_EQ(findMaxSignal(getSignalA, prg, 0), 65210);
	}

	TEST(NAME, InputA)
	{
		std::string prg = "3,8,1001,8,10,8,105,1,0,0,21,46,59,80,105,122,203,284,365,446,99999,3,9,102,3,9,9,1001,9,5,9,102,2,9,9,1001,9,3,9,102,4,9,9,4,9,99,3,9,1002,9,2,9,101,2,9,9,4,9,99,3,9,101,5,9,9,1002,9,3,9,1001,9,3,9,1002,9,2,9,4,9,99,3,9,1002,9,4,9,1001,9,2,9,102,4,9,9,101,3,9,9,102,2,9,9,4,9,99,3,9,102,5,9,9,101,4,9,9,102,3,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,99,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,99";
		EXPECT_EQ(findMaxSignal(getSignalA, prg, 0), 880726);
	}

	TEST(NAME, ExampleB1)
	{
		std::string prg = "3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5";
		EXPECT_EQ(findMaxSignal(getSignalB, prg, 5), 139629729);
	}

	TEST(NAME, ExampleB2)
	{
		std::string prg = "3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,-5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10";
		EXPECT_EQ(findMaxSignal(getSignalB, prg, 5), 18216);
	}

	TEST(NAME, InputB)
	{
		std::string prg = "3,8,1001,8,10,8,105,1,0,0,21,46,59,80,105,122,203,284,365,446,99999,3,9,102,3,9,9,1001,9,5,9,102,2,9,9,1001,9,3,9,102,4,9,9,4,9,99,3,9,1002,9,2,9,101,2,9,9,4,9,99,3,9,101,5,9,9,1002,9,3,9,1001,9,3,9,1002,9,2,9,4,9,99,3,9,1002,9,4,9,1001,9,2,9,102,4,9,9,101,3,9,9,102,2,9,9,4,9,99,3,9,102,5,9,9,101,4,9,9,102,3,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,99,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,99";
		EXPECT_EQ(findMaxSignal(getSignalB, prg, 5), 4931744);
	}
}