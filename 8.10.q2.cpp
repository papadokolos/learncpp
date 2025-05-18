#include <print>


int sumTo(int value)
{
    int sum{ 0 };
    for (int current_value{ 1 }; current_value <= value; ++current_value)
    {
        sum += current_value;
    }

    return sum;
}

int main(int /*argc*/, char const */*argv*/[])
{
    std::print("{}", sumTo(5));

    return 0;
}