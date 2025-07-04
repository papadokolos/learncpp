#include "CInTools.h"

#include <print>


constexpr int perfectSquares[]{ 0, 1, 4, 9 };

bool isPerfectSquare(int value)
{
    for (int perfectSquare : perfectSquares)
    {
        if (value == perfectSquare)
        {
            return true;
        }
    }

    return false;
}

int main(int /*argc*/, char const */*argv*/[])
{
    constexpr int exitInput{ -1 };

    while (true)
    {
        int input{ Input::get<int>("Enter a single digit integer, or -1 to quit: ")};
        if (input == exitInput)
        {
            std::println("Bye");
            break;
        }

        std::println(
            "{} is {}a perfect square",
            input,
            isPerfectSquare(input) ? "" : "not ");
    }


    return 0;
}