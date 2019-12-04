#include "pch.h"

namespace
{
	void populate(size_t i, int* d)
	{
		d[0] = i / 100000 % 10;
		d[1] = i / 10000 % 10;
		d[2] = i / 1000 % 10;
		d[3] = i / 100 % 10;
		d[4] = i / 10 % 10;
		d[5] = i % 10;
	}

	TEST(Day04, InputA)
	{
		int count = 0;
		for (size_t i = 147981; i < 691423; i++)
		{
			int d[6];
			populate(i, d);

			bool twoSame = false;
			bool notIncreasing = false;
			for (size_t i = 0; i < 5; i++)
			{
				if (d[i] == d[i + 1])
				{
					twoSame = true;
				}
				if (d[i] > d[i + 1])
				{
					notIncreasing = true;
				}
			}

			if (twoSame && !notIncreasing)
			{
				count++;
			}
		}

		EXPECT_EQ(count, 1790);
	}

	TEST(Day04, InputB)
	{
		int count = 0;
		for (size_t i = 147981; i < 691423; i++)
		{
			int d[6];
			populate(i, d);

			bool exactlyTwoSame = false;
			for (int i = -1; i <= 4; i++)
			{
				bool a = true;
				if (i >= 0)
				{
					a = d[i] != d[i + 1];
				}

				bool b = d[i + 1] == d[i + 2];

				bool c = true;
				if (i <= 3)
				{
					c = d[i + 2] != d[i + 3];
				}
				if (a && b && c)
				{
					exactlyTwoSame = true;
					break;
				}
			}

			bool notIncreasing = false;
			for (size_t i = 0; i < 5; i++)
			{
				if (d[i] > d[i + 1])
				{
					notIncreasing = true;
				}
			}

			if (exactlyTwoSame && !notIncreasing)
			{
				count++;
			}
		}

		EXPECT_EQ(count, 1206);
	}
}
