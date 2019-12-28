#include "pch.h"
#include "md5.h"

namespace
{
    // To be able to re-run this fast the start is non-zero in tests (six zeroes takes about 3 minutes)
    int calculateA(std::string input, int start, int zeros)
    {
        for (int i = start; i < std::numeric_limits<int>::max(); i++)
        {
            std::string in = input + std::to_string(i);
            std::string hashed = md5(in);

            bool found = true;
            for (int i = 0; i < zeros; i++)
            {
                if (!(found && hashed[i] == '0'))
                {
                    found = false;
                }
            }

            if (found)
            {
                return i;
            }
        }
        return -1;
    }

    TEST(Day04, ExampleA1)
    {
        EXPECT_EQ(calculateA("abcdef", 609043, 5), 609043);
    }

    TEST(Day04, ExampleA2)
    {
        EXPECT_EQ(calculateA("pqrstuv", 1048970, 5), 1048970);
    }

    TEST(Day04, InputA)
    {
        EXPECT_EQ(calculateA("yzbqklnj", 282749, 5), 282749);
    }

    TEST(Day04, InputB)
    {
        EXPECT_EQ(calculateA("yzbqklnj", 9962624, 6), 9962624);
    }
}
