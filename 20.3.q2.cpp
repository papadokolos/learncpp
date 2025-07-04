#include <print>

int sumDigits(int n)
{
    if (n == 0)
    {
        return 0;
    }

    return (n % 10) + sumDigits(n / 10);
}


int main(int /*argc*/, char const */*argv*/[])
{
    std::println("Sum of digits of 93427: {}", sumDigits(93427));

    return 0;
}
