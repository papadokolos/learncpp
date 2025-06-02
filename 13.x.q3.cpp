#include <print>


template <typename T>
struct Triad
{
    T first {};
    T second {};
    T third {};
};

template <typename T>
void print(const Triad<T>& triad)
{
    std::print("[{}, {}, {}]", triad.first, triad.second, triad.third);
}

int main()
{
    Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
    print(t1);

    Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
    print(t2);

    return 0;
}