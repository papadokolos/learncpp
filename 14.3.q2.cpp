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

    bool isEqual(IntPair other) const  // Small enough to pass by value
    {
        return (first == other.first)
            && (second == other.second);
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

    std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
    std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

    return 0;
}