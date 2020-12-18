#include "pch.h"
#include "aoc.h"

#define NAME Day08__Handheld_Halting
// https://adventofcode.com/2020/day/8

namespace
{
	std::stringstream GetExampleData()
    {
        std::stringstream ss;
        ss.str(R"(
nop +0
acc +1
jmp +4
acc +3
jmp -3
acc -99
acc +1
jmp -4
acc +6
)");
        return ss;
    }

    enum class Operation
    {
        acc,
        jmp,
        nop
    };

    struct Instruction
    {
        Instruction(Operation op, int arg)
            : Op(op), Arg(arg)
        {};
        
        Operation Op;
        int Arg;
    };

    typedef std::vector<Instruction> Program;

    Operation StringToOperation(const std::string& s)
    {
        if (s == "acc") return Operation::acc;
        if (s == "jmp") return Operation::jmp;
        if (s == "nop") return Operation::nop;
        throw std::runtime_error("Unknown operation.");
    }

    Program Parse(std::stringstream input)
    {
        Program prg;
        for (std::string line; std::getline(input, line); ) 
        {
            if (line.size() == 0) continue;
            prg.emplace_back(StringToOperation(line.substr(0,3)), std::stoi(line.substr(4, line.size())));
        }
        return prg;
    }

    struct ExecutionResult
    {
        bool InfiniteLoop;
        int Accumulator;
    };

    ExecutionResult Execute(const Program& prg)
    {
        unsigned int counter = 0;
        int acc = 0;
        std::unordered_set<unsigned int> executedInstructions;
        while(true)
        {
            if (executedInstructions.count(counter) > 0)
            {
                return { true, acc };
            }
            if (counter >= prg.size())
            {
                return { false, acc };
            }
            executedInstructions.insert(counter);
            switch (prg[counter].Op)
            {
            case Operation::acc:
                acc += prg[counter].Arg;
                counter++;
                break;
            case Operation::nop:
                counter++;
                break;
            case Operation::jmp:
                counter += prg[counter].Arg;
                break;
            default:
                throw std::runtime_error("Unknown operation.");
            }
        }
    }

	TEST(NAME, ExampleA)
	{
		Program prg = Parse(GetExampleData());
        int result = Execute(prg).Accumulator;
		EXPECT_EQ(result, 5);
	}

    TEST(NAME, InputA)
	{
		Program prg = Parse(aoc::readInputFile("Day08.txt"));
        int result = Execute(prg).Accumulator;
		EXPECT_EQ(result, 1801);
	}

    int FixAndExecute(Program prg)
    {
        ExecutionResult result;
        for (size_t i = 0; i < prg.size(); i++)
        {
            if (prg[i].Op == Operation::jmp)
            {
                prg[i].Op = Operation::nop;
                result = Execute(prg);
                if (!result.InfiniteLoop) break;
                prg[i].Op = Operation::jmp;
            }
            if (prg[i].Op == Operation::nop)
            {
                prg[i].Op = Operation::jmp;
                result = Execute(prg);
                if (!result.InfiniteLoop) break;
                prg[i].Op = Operation::nop;
            }
        }
        return result.Accumulator;
    }

    TEST(NAME, ExampleB)
	{
		Program prg = Parse(GetExampleData());
        int result = FixAndExecute(prg);
		EXPECT_EQ(result, 8);
	}

    TEST(NAME, InputB)
	{
		Program prg = Parse(aoc::readInputFile("Day08.txt"));
        int result = FixAndExecute(prg);
		EXPECT_EQ(result, 2060);
	}
}
