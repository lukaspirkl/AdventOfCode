#pragma once
#include "aoc.h"

namespace aoc
{
	class intcode
	{
	private:
		std::vector<long long> data;
		size_t originalDataSize = 0;
		size_t pc = 0;
		size_t pcWhenStopped = std::numeric_limits<size_t>::max();
		size_t relativeBase = 0;
		long long get(int param);
		void set(int param, long long value);

	public:
		enum class result
		{
			inputRequested,
			outputProvided,
			programEnded
		};

		long long io;

		intcode(const std::vector<long long>& data);
		intcode(const std::string& data);

		std::vector<long long> getData();
		int getInstruction();
		void run(long long input, std::vector<long long>& output = std::vector<long long>());
		void run(std::queue<long long>& input, std::vector<long long>& output = std::vector<long long>());
		intcode::result run();
	};
}
