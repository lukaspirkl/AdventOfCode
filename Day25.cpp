#include "pch.h"
#include "aoc.h"
#include "intcode.h"

#define NAME Day25__Cryostasis

namespace 
{
	class computer
	{
	private:
		aoc::intcode intcode;
		aoc::intcode::result lastResult;
		std::vector<std::string> items{ "manifold","dehydrated water","polygon","weather machine","bowl of rice","hypercube","candy cane","dark matter" };

	public:
		computer()
			: intcode(aoc::readInputFile("Day25.txt").str())
		{
			lastResult = intcode.run();
		}

		std::string run(const std::string& input)
		{
			std::stringstream out;
			size_t inputIndex = 0;

			while (lastResult != aoc::intcode::result::programEnded)
			{
				if (lastResult == aoc::intcode::result::inputRequested)
				{
					if (inputIndex >= input.size())
					{
						return out.str();
					}

					intcode.io = input[inputIndex];
					inputIndex++;
					out.str("");
				}
				else if (lastResult == aoc::intcode::result::outputProvided)
				{
					out << (char)intcode.io;
				}

				lastResult = intcode.run();
			}
			return out.str();
		}

		std::string useItemCombination(const std::string& command, uint8_t i)
		{
			std::stringstream input;
			for (size_t bit = 0; bit < 8; bit++)
			{
				if ((i >> bit) & 1)
				{
					input << command << " " << items[bit] << "\n";
				}
			}
			input << "south\n";
			return run(input.str());
		}
	};

	TEST(NAME, InputA)
	{
		computer c;

		//Move all safe items to Security Checkpoint
		std::string out = c.run(R"(east
take weather machine
west
west
west
take bowl of rice
east
north
take polygon
east
take hypercube
south
take dark matter
north
west
north
take candy cane
west
north
take manifold
south
west
north
take dehydrated water
west
)");
		out = c.useItemCombination("drop", 255); // drop all

		// Try all combination until message is different (8 items = 8 bits)
		for (uint8_t i = 1; i <= std::numeric_limits<uint8_t>::max(); i++)
		{
			out = c.useItemCombination("take", i);

			if (out.find("Alert! Droids on this ship are heavier than the detected value!") == std::string::npos &&
				out.find("Alert! Droids on this ship are lighter than the detected value!") == std::string::npos)
			{
				break;
			}

			out = c.useItemCombination("drop", i);
		}

		EXPECT_TRUE(out.find("10504192") != std::string::npos);
	}
}


/*

+---------------------+----------+------------------------+---------------+-------------+                                                
| Security Checkpoint = Corridor | Hot Chocolate Fountain = SickBay       | Engineering |                                                
+------|  |-----------+---|  |---+------------------------+-----|  |-----+----|  |------+                                                
| Pressure sensitive  |           Stables                 = Crew Quarters = Hallway     |                                                
+---------------------+---|  |---+------------------------+---------------+---|  |------+------------------------+----------------------+
                      | Holodeck |                                        |                                      = Storage              |
                      +----------+                                        | Kitchen     +------------------------+-----|  |-------------+
                                                                          |             | Passages               = Observatory          |
                                                          +---------------+---|  |------+------------------------+----------------------+
                                                          | Arcade        = Navigation  = Hull Breach            = Gift Wrapping Center |
                                                          +---------------+-------------+------|  |--------------+----------------------+
                                                                                        | Warp Drive Maintenance |                       
                                                                                        +------|  |--------------+                       
                                                                                        | Sience Lab             |                       
                                                                                        +------------------------+                       


*/