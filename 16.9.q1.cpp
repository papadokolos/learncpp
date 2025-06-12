#include <cassert>
#include <vector>
#include <print>
#include <source_location>


namespace Animals
{
    constexpr auto enumStart{ std::source_location::current().line() };
    enum Type
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
    };
    constexpr auto enumEnd{ std::source_location::current().line() };
    constexpr int overheadLines{ 4 };
    constexpr int numAnimals{ enumEnd - enumStart - overheadLines };

    const std::vector<int> legsPerAnimal{ 2, 4, 4, 4, 2, 0 };
}


int main(int /*argc*/, char const */*argv*/[])
{
    assert(std::ssize(Animals::legsPerAnimal) == Animals::numAnimals);

    std::println(
        "An elephant has {} legs.",
        Animals::legsPerAnimal[Animals::elephant]);

    return 0;
}