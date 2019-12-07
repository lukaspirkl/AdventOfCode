#pragma once
#include "pch.h"
#include "aoc.h"

namespace aoc
{
	class intcode
	{
	private:
		std::vector<int> data;
		size_t pc = 0;
		size_t pcWhenStopped = std::numeric_limits<size_t>::max();
		int get(int param);
		void set(int param, int value);

	public:
		enum class result
		{
			inputRequested,
			outputProvided,
			programEnded
		};

		int io;

		intcode(std::vector<int> data);
		intcode(const std::string& data);
		
		std::vector<int> getData();
		int getInstruction();
		void run(int input, std::vector<int>& output = std::vector<int>());
		void run(std::queue<int>& input, std::vector<int>& output = std::vector<int>());
		intcode::result run();
	};
}
