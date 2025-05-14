#include <print>


int main(int /*argc*/, char const */*argv*/[])
{
    constexpr char begin_char { 'a' };
    constexpr char end_char { 'z' };

    char current_char { begin_char };
    while (current_char <= end_char)
    {
        std::println(
            "'{}' {:d}", current_char, current_char);
        ++current_char;
    }

    return 0;
}