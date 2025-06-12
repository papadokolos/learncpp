#include <cassert>
#include <iterator>
#include <print>
#include <string_view>
#include <vector> // for std::vector, std::size_t


void fizzBuzz(int upTo)
{
    const std::vector<int> divisors{ 3, 5, 7, 11, 13, 17, 19 };
    const std::vector<std::string_view> words{
        "fizz", "buzz", "pop", "bang", "jazz", "pow", "boom" };
    assert(std::size(divisors) == std::size(words));

    for (int counter{ 1 }; counter <= upTo; ++counter)
    {
        bool nonDivisible{ true };
        for (std::size_t index{ 0 }; index < divisors.size(); ++index)
        {
            if (counter % divisors[index] == 0)
            {
                nonDivisible = false;
                std::print("{}", words[index]);
            }
        }

        if (nonDivisible)
        {
            std::print("{}", counter);
        }

        std::println();
    }
}


int main(int /*argc*/, char const */*argv*/[])
{
    fizzBuzz(150);

    return 0;
}