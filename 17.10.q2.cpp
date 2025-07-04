#include <iterator>
#include <print>


template <auto N>
void printCStringBackwards1(const char (&str)[N])
{
    for (
        const char* pChar{ &str[std::size(str) - 1] }; // Invariant size(str)>=0
        pChar >= str;
        --pChar)
    {
        std::print("{}", *pChar);
    }

    std::println();
}

void printCStringBackwards2(const char str[])
{
    // Invariant: str is null terminated (property of C-style string)
    const char* strIterator{ str };

    while (*strIterator != '\0') { ++strIterator; }
    // --strIterator; // Optional: Move one step before null terminating char
    while (strIterator-- != str)
    {
        std::print("{}", *strIterator);
    }

    std::println();
}


int main(int /*argc*/, char const */*argv*/[])
{
    constexpr char str[]{ "Hello, world!" };

    printCStringBackwards1(str);
    printCStringBackwards2(str);


    return 0;
}
