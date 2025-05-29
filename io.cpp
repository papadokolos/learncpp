#include "io.h"
#include <iostream>


int readNumber()
{
    int number{};
    std::cin >> number;

    return number;
}

void writeAnswer(int answer)
{
    std::cout << answer << "\n";
}