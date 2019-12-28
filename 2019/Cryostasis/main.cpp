#include <iostream>
#include "input.h"
#include "aoc.h"
#include "intcode.h"

int main()
{
    aoc::intcode intcode(input);

    bool running = true;
    while(running)
    {
        switch (intcode.run())
        {
        case aoc::intcode::result::inputRequested:
            intcode.io = getchar();
            break;
        case aoc::intcode::result::outputProvided:
            std::cout << (char)intcode.io;
            break;
        case aoc::intcode::result::programEnded:
            running = false;
            break;
        default:
            break;
        }
    }

    std::cout << "Program ended. Press enter." << std::endl;
    getchar();
    return 0;
}
