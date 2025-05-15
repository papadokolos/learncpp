#include <iostream>


constexpr bool isEven(int number)
{
    return (number % 2) == 0;
}


int main()
{
    std::print("Enter an integer: ");
    int number{};
    std::cin >> number;

    std::string_view evinness{};
    if (isEven(number))
    {
        evinness = "even";
    }
    else
    {
        evinness = "odd";
    }

    std::println("{} is {}", number, evinness);

    return 0;
}