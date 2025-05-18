#include <print>


void fizzbuzz(int max)
{
    for (int number { 1 }; number <= max; ++number)
    {
        const bool divisible_by_3{ number % 3 == 0 };
        const bool divisible_by_5{ number % 5 == 0 };
        const bool divisible_by_7{ number % 7 == 0 };

        if (divisible_by_3)
            std::print("fizz");
        if (divisible_by_5)
            std::print("buzz");
        if (divisible_by_7)
            std::print("pop");
        if (!divisible_by_3 && !divisible_by_5 && !divisible_by_7)
            std::print("{}", number);

        std::println();
    }
}

int main(int /*argc*/, char const */*argv*/[])
{
    constexpr int count_to{ 150 };
    fizzbuzz(count_to);

    return 0;
}