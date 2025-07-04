#include "CInTools.h"

#include <algorithm>
#include <cstddef>
#include <format>
#include <print>
#include <string>


void fillNamesFromCLI(std::string names[], int namesLength)
{
    for (int index{ 0 }; index < namesLength; ++index)
    {
        names[index] =
            Input::get<std::string>(
                std::format("Enter name #{}: ", index + 1));
    }
}

void printNames(std::string names[], int namesLength)
{
    std::println("Here is your sorted list:");
    for (int index{ 0 }; index < namesLength; ++index)
    {
        std::println("Name #{}: {}", index + 1, names[index]);
    }
}

int main(int /*argc*/, char const */*argv*/[])
{
    const int numNames{
        Input::get<int>("How many names would you like to enter? ") };
    auto names{ new std::string[static_cast<std::size_t>(numNames)]{} };
    fillNamesFromCLI(names, numNames);

    std::ranges::sort(names, names + numNames);

    std::println();
    printNames(names, numNames);

    delete[] names;
    // names = nullptr;

    return 0;
}
