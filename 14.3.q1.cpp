#include <iostream>
#include <print>

// Provide the definition for IntPair and the print() member function here
struct IntPair
{
    int first {};
    int second {};

    void print() const
    {
        std::println("Pair({}, {})", first, second);
    }
};

int main()
{
    IntPair p1 {1, 2};
    IntPair p2 {3, 4};

    std::cout << "p1: ";
    p1.print();

    std::cout << "p2: ";
    p2.print();

    return 0;
}