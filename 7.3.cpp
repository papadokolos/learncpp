#include <cstdio>
#include <iostream>
#include <utility>


int main(int /*argc*/, char const */*argv*/[])
{
    std::print("Enter an integer: ");
    int smaller{};
    std::cin >> smaller;

    std::print("Enter a larger integer: ");
    int larger{};
    std::cin >> larger;

    if (larger < smaller)
    {
        std::puts("Swapping the values");
        // int temp{ smaller };
        // smaller = larger;
        // larger = temp;
        std::swap(smaller, larger);
    }

    std::println("The smaller value is {}", smaller);
    std::println("The larger value is {}", larger);


    return 0;
}