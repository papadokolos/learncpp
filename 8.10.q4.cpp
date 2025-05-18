#include <print>


void fizzbuzz(int max)
{
    for (int number { 1 }; number <= max; ++number)
    {
        const bool divisible_by_3{ number % 3 == 0 };
        const bool divisible_by_5{ number % 5 == 0 };

        if (divisible_by_3 && divisible_by_5)
            std::puts("fizzbuzz");
        else if (divisible_by_3)
            std::puts("fizz");
        else if (divisible_by_5)
            std::puts("buzz");
        else
            std::println("{}", number);
    }
}

int main(int /*argc*/, char const */*argv*/[])
{
    constexpr int count_to{ 15 };
    fizzbuzz(count_to);

    return 0;
}