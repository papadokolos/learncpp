#include <print>
#include <iostream>
#include <string>

template <typename T, typename U, typename V>
class Triad
{
public:
    Triad(const T& first, const U& second, const V& third);

    const T& getFirst() const { return m_first; }
    const U& getSecond() const { return m_second; }
    const V& getThird() const { return m_third; }

    void print() const;

private:
    T m_first {};
    U m_second {};
    V m_third {};
};

template <typename T, typename U, typename V>
Triad<T, U, V>::Triad(const T& first, const U& second, const V& third)
    : m_first  { first }
    , m_second { second }
    , m_third  { third }
{}

template <typename T, typename U, typename V>
void Triad<T, U, V>::print() const
{
    std::print("[{}, {}, {}]", m_first, m_second, m_third);
}


int main()
{
    Triad<int, int, int> t1{ 1, 2, 3 };
    t1.print();
    std::cout << '\n';
    std::cout << t1.getFirst() << '\n';

    using namespace std::literals::string_literals;
    const Triad t2{ 1, 2.3, "Hello"s };
    t2.print();
    std::cout << '\n';

    return 0;
}