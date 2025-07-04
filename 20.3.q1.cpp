#include <print>

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }

    return n * factorial(n - 1);
}


int main(int /*argc*/, char const */*argv*/[])
{
    for (int num{ 0 }; num < 7; ++num)
    {
        std::println("Factorial of {}: {}", num, factorial(num));
    }

    return 0;
}
