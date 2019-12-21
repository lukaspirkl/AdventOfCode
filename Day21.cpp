#include "pch.h"
#include "aoc.h"
#include "intcode.h"

namespace
{
	/*

. -> false
# -> true

AND X Y sets Y to true if both X and Y are true; otherwise, it sets Y to false.
OR X Y sets Y to true if at least one of X or Y is true; otherwise, it sets Y to false.
NOT X Y sets Y to true if X is false; otherwise, it sets Y to false.
	
	......@.......@....
	#####.#.###########
	       ABCD    ABCD

	..@..............
	#####.#.#...#####
	   ABCDEFGHI

	....@............
	#####...###..####

	
	NOT A T	- A:false	T:false	->	T:true
	AND D T	- D:true	T:true	->	T:true
	AND H T
	 OR T J	- T:true	J:false ->	J:true
	NOT B T	- B:false	T:true
	AND D T	- D:true	T:true
	 OR T J
	NOT C T	- C:false	T:true
	AND D T	- D:true	T:true
	 OR T J
	NOT A T
	 OR T J


	*/
	int process(const std::string& prg, std::stringstream& out)
	{
		aoc::intcode intcode(aoc::readInputFile("Day21.txt").str());
		aoc::intcode::result r;
		size_t i = 0;
		bool running = true;
		int result = 0;
		while (running)
		{
			r = intcode.run();
			switch (r)
			{
			case aoc::intcode::result::inputRequested:
				intcode.io = prg[i];
				i++;
				break;
			case aoc::intcode::result::outputProvided:
				out << (char)intcode.io;
				result = (int)intcode.io;
				break;
			case aoc::intcode::result::programEnded:
				running = false;
				break;
			default:
				break;
			}
		}
		return result;
	}

	TEST(Day21, InputA)
	{
		std::string prg = "NOT A T\nAND D T\nOR T J\nNOT B T\nAND D T\nOR T J\nNOT C T\nAND D T\nOR T J\nWALK\n";
		std::stringstream out;
		int result = process(prg, out);
		std::string s = out.str();
		EXPECT_EQ(result, 19357180);
	}

	TEST(Day21, InputB)
	{
		std::string prg = "NOT A T\nAND D T\nAND H T\nOR T J\nNOT B T\nAND D T\nAND H T\nOR T J\nNOT C T\nAND D T\nAND H T\nOR T J\nNOT A T\nOR T J\nRUN\n";
		std::stringstream out;
		int result = process(prg, out);
		std::string s = out.str();
		EXPECT_EQ(result, 1139793906);
	}
}
