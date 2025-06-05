#include <print>
#include <vector>


int main(int /*argc*/, char const */*argv*/[])
{
    std::vector<char> word{ 'h', 'e', 'l', 'l', 'o' };
    std::println("The array has {} elements.", std::size(word));
    std::println("{}{}", word[1], word.at(1));

    return 0;
}