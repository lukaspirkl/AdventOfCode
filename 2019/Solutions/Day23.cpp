#include "pch.h"
#include "aoc.h"
#include "intcode.h"

#define NAME Day23__Category_Six

namespace
{
	typedef std::pair<long long, long long> packet;

	struct computer
	{
		aoc::intcode intcode;
		std::queue<packet> received;
		aoc::intcode::intcode::result lastResult;
	};

	std::vector<computer> create()
	{
		auto input = aoc::splitLongLong(aoc::readInputFile("Day23.txt").str());

		std::vector<computer> computers(50, computer{ aoc::intcode(input), std::queue<packet>() });

		for (size_t i = 0; i < 50; i++)
		{
			auto r = computers[i].intcode.run();
			if (r != aoc::intcode::result::inputRequested)
			{
				throw std::runtime_error("Input not requested during initialization.");
			}
			computers[i].intcode.io = i;
			computers[i].lastResult = computers[i].intcode.run();
		}

		return computers;
	}

	long long compute(std::vector<computer>& computers)
	{
		while (true)
		{
			for (size_t i = 0; i < 50; i++)
			{
				auto& c = computers[i];
				if (c.lastResult == aoc::intcode::result::inputRequested)
				{
					if (c.received.size() == 0)
					{
						c.intcode.io = -1;
						c.lastResult = c.intcode.run();
					}
					else
					{
						c.intcode.io = c.received.front().first;
						auto r = c.intcode.run();
						if (r != aoc::intcode::result::inputRequested)
						{
							throw std::runtime_error("Input not requested for second packet data.");
						}
						c.intcode.io = c.received.front().second;
						c.received.pop();
						c.lastResult = c.intcode.run();
					}
				}
				else if (c.lastResult == aoc::intcode::result::outputProvided)
				{
					while (c.lastResult == aoc::intcode::result::outputProvided)
					{
						long long address = c.intcode.io;
						packet packet;
						auto r = c.intcode.run();
						if (r != aoc::intcode::result::outputProvided)
						{
							throw std::runtime_error("Output not provided for first packet data.");
						}
						packet.first = c.intcode.io;
						r = c.intcode.run();
						if (r != aoc::intcode::result::outputProvided)
						{
							throw std::runtime_error("Output not provided for second packet data.");
						}
						packet.second = c.intcode.io;
						if (address == 255)
						{
							return packet.second;
						}
						computers[address].received.push(packet);
						c.lastResult = c.intcode.run();
					}
				}
				else
				{
					throw std::runtime_error("Program ended.");
				}
			}
		}
	}

	TEST(NAME, InputA)
	{
		auto input = create();
		EXPECT_EQ(compute(input), 23626);
	}

	long long computeWithNAT(std::vector<computer>& computers)
	{
		packet natPacket;
		bool natPacketSet = false;
		long long lastY = 0;

		while (true)
		{
			bool isIdle = true;

			for (size_t i = 0; i < 50; i++)
			{
				auto& c = computers[i];
				if (c.lastResult == aoc::intcode::result::inputRequested)
				{
					if (c.received.size() == 0)
					{
						c.intcode.io = -1;
						c.lastResult = c.intcode.run();
					}
					else
					{
						isIdle = false;
						c.intcode.io = c.received.front().first;
						auto r = c.intcode.run();
						if (r != aoc::intcode::result::inputRequested)
						{
							throw std::runtime_error("Input not requested for second packet data.");
						}
						c.intcode.io = c.received.front().second;
						c.received.pop();
						c.lastResult = c.intcode.run();
					}
				}
				else if (c.lastResult == aoc::intcode::result::outputProvided)
				{
					isIdle = false;
					while (c.lastResult == aoc::intcode::result::outputProvided)
					{
						long long address = c.intcode.io;
						packet packet;
						auto r = c.intcode.run();
						if (r != aoc::intcode::result::outputProvided)
						{
							throw std::runtime_error("Output not provided for first packet data.");
						}
						packet.first = c.intcode.io;
						r = c.intcode.run();
						if (r != aoc::intcode::result::outputProvided)
						{
							throw std::runtime_error("Output not provided for second packet data.");
						}
						packet.second = c.intcode.io;
						if (address == 255)
						{
							natPacket = packet;
							natPacketSet = true;
						}
						else
						{
							computers[address].received.push(packet);
						}
						c.lastResult = c.intcode.run();
					}
				}
				else
				{
					throw std::runtime_error("Program ended.");
				}
			}
			
			if (isIdle && natPacketSet)
			{
				if (lastY == natPacket.second)
				{
					return lastY;
				}
				lastY = natPacket.second;
				computers[0].received.push(natPacket);
				natPacketSet = false;
			}
		}
	}

	TEST(NAME, InputB)
	{
		auto input = create();
		EXPECT_EQ(computeWithNAT(input), 19019);
	}
}
