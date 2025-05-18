#include <print>


int main(int /*argc*/, char const */*argv*/[])
{
    for (int number{ 0 }; number <= 20; number += 2)
    {
        std::println("{}", number);
    }

    return 0;
}