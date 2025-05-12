#include <iostream>
#include <string_view>

std::string_view getQuantityPhrase(int quantity)
{
    std::string_view phrase{};

    if (quantity < 0)
        phrase = "negative";
    else if (quantity == 0)
        phrase = "no";
    else if (quantity == 1)
        phrase = "a single";
    else if (quantity == 2)
        phrase = "a couple of";
    else if (quantity == 3)
        phrase = "a few";
    else if (quantity > 3)
        phrase = "many";

    return phrase;
}

std::string_view getApplesPluralized(int quantity)
{
    return (quantity == 1) ? "apple" : "apples";
}

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";


    return 0;
}