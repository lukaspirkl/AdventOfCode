#include "pch.h"
#include "intcode.h"

namespace aoc
{
	intcode::intcode(std::vector<int> data)
	{
		this->data = data;
	}

	intcode::intcode(const std::string& data)
	{
		this->data = aoc::splitInt(data);
	}

	std::vector<int> intcode::getData()
	{
		return data;
	}

	int intcode::getInstruction()
	{
		return data[pc] % 100;
	}

	int intcode::get(int param)
	{
		int parameterMode = data[pc] / (int)pow(10, param + 2) % 10;
		if (parameterMode == 1)
		{
			return data[pc + param + 1];
		}
		else
		{
			return data[data[pc + param + 1]];
		}
	}

	void intcode::set(int param, int value)
	{
		data[data[pc + param + 1]] = value;
	}

	void intcode::run(int input, std::vector<int>& output)
	{
		std::queue<int> inputQueue;
		inputQueue.push(input);
		run(inputQueue, output);
	}

	void intcode::run(std::queue<int>& input, std::vector<int>& output)
	{
		while (true)
		{
			switch (run())
			{
			case intcode::result::programEnded:
				return;
			case intcode::result::inputRequested:
				io = input.front();
				input.pop();
				break;
			case intcode::result::outputProvided:
				output.push_back(io);
				break;
			default:
				//TODO: Throw exception or something
				return;
				break;
			}
		}
	}

	intcode::result intcode::run()
	{
		while (getInstruction() != 99)
		{
			switch (getInstruction())
			{
			case 1:
				set(2, get(0) + get(1));
				pc += 4;
				break;
			case 2:
				set(2, get(0) * get(1));
				pc += 4;
				break;
			case 3:
				if (pcWhenStopped != pc)
				{
					pcWhenStopped = pc;
					return intcode::result::inputRequested;
				}
				set(0, io);
				pc += 2;
				break;
			case 4:
				if (pcWhenStopped != pc)
				{
					pcWhenStopped = pc;
					io = get(0);
					return intcode::result::outputProvided;
				}
				pc += 2;
				break;
			case 5:
				if (get(0) != 0)
				{
					pc = get(1);
				}
				else
				{
					pc += 3;
				}
				break;
			case 6:
				if (get(0) == 0)
				{
					pc = get(1);
				}
				else
				{
					pc += 3;
				}
				break;
			case 7:
				if (get(0) < get(1))
				{
					set(2, 1);
				}
				else
				{
					set(2, 0);
				}
				pc += 4;
				break;
			case 8:
				if (get(0) == get(1))
				{
					set(2, 1);
				}
				else
				{
					set(2, 0);
				}
				pc += 4;
				break;
			default:
				//TODO: Throw exception or something
				return intcode::result::programEnded;
				break;
			}
		}
		return intcode::result::programEnded;
	}
}
