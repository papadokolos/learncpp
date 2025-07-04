#include <iterator>
#include <print>


template <auto N>
void printCString1(const char (&str)[N])
{
    for (
        const char* pChar{ str };
        pChar <= &str[std::size(str) - 1]; // Invariant size(str)>=0
        ++pChar)
    {
        std::print("{}", *pChar);
    }

    std::println();
}

void printCString2(const char str[])
{
    // Invariant: str is null terminated (property of C-style string)
    while (*str != '\0')
    {
        std::print("{}", *str);
        ++str;
    }

    std::println();
}


int main(int /*argc*/, char const */*argv*/[])
{
    constexpr char str[]{ "Hello, world!" };

    printCString1(str);
    printCString2(str);


    return 0;
}
