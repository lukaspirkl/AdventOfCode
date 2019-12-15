#include "pch.h"
#include "intcode.h"

namespace aoc
{
	intcode::intcode(std::vector<long long> data)
	{
		this->originalDataSize = data.size();
		this->data = std::vector<long long>(100000);
		for (size_t i = 0; i < data.size(); i++)
		{
			this->data[i] = data[i];
		}
	}

	intcode::intcode(const std::string& data) : intcode(aoc::splitLongLong(data))
	{
	}

	std::vector<long long> intcode::getData()
	{
		return std::vector<long long>(data.begin(), data.begin() + originalDataSize);
	}

	int intcode::getInstruction()
	{
		return data[pc] % 100;
	}

	long long intcode::get(int param)
	{
		int parameterMode = data[pc] / (int)pow(10, param + 2) % 10;
		if (parameterMode == 1)
		{
			return data[pc + param + 1];
		}
		else if (parameterMode == 2)
		{
			return data[relativeBase + data[pc + param + 1]];
		}
		else
		{
			return data[data[pc + param + 1]];
		}
	}

	void intcode::set(int param, long long value)
	{
		int parameterMode = data[pc] / (int)pow(10, param + 2) % 10;
		if (parameterMode == 1)
		{
			throw std::exception("Invalid parameter mode (1) when setting value.");
			//data[pc + param + 1] = value;
		}
		else if (parameterMode == 2)
		{
			data[relativeBase + data[pc + param + 1]] = value;
		}
		else
		{
			data[data[pc + param + 1]] = value;
		}
	}

	void intcode::run(long long input, std::vector<long long>& output)
	{
		std::queue<long long> inputQueue;
		inputQueue.push(input);
		run(inputQueue, output);
	}

	void intcode::run(std::queue<long long>& input, std::vector<long long>& output)
	{
		while (true)
		{
			auto result = run();
			switch (result)
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
				throw std::exception("Unknown intcode result.");
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
				pcWhenStopped = std::numeric_limits<size_t>::max();
				pc += 2;
				break;
			case 4:
				if (pcWhenStopped != pc)
				{
					pcWhenStopped = pc;
					io = get(0);
					return intcode::result::outputProvided;
				}
				pcWhenStopped = std::numeric_limits<size_t>::max();
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
			case 9:
				relativeBase += get(0);
				pc += 2;
				break;
			default:
				throw std::exception("Unknown opcode.");
				break;
			}
		}
		return intcode::result::programEnded;
	}
}
