#include <numeric>
#include <print>


class Fraction
{
public:
    Fraction() = default;
    explicit Fraction(int numerator) : m_numerator{ numerator } {}
    Fraction(int numerator, int denominator);

    void print() const { std::println("{}/{}", m_numerator, m_denominator); }
    void reduce();

    // Pass by-value since Fraction is small
    friend Fraction operator*(Fraction lhs, Fraction rhs);
    friend Fraction operator*(Fraction lhs, int rhs);
    friend Fraction operator*(int lhs, Fraction rhs);

    // Not asked for by the exercise, but for good practice
    Fraction& operator+=(Fraction other);
    Fraction& operator+=(int other);

private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };
};

Fraction::Fraction(int numerator, int denominator)
    : m_numerator{ numerator }, m_denominator{ denominator }
{
    reduce();
}

void Fraction::reduce()
{
    const int gcd{ std::gcd(m_numerator, m_denominator) };
    if (gcd != 0)
    {
        m_numerator /= gcd;
        m_denominator /= gcd;
    }
}

Fraction operator*(Fraction lhs, Fraction rhs)
{
    return Fraction{
        lhs.m_numerator * rhs.m_numerator,
        lhs.m_denominator * rhs.m_denominator
    };
}

Fraction operator*(Fraction lhs, int rhs)
{
    return Fraction{
        lhs.m_numerator * rhs,
        lhs.m_denominator
    };
}

Fraction operator*(int lhs, Fraction rhs)
{
    return rhs * lhs;
}

int main(int /*argc*/, char const */*argv*/[])
{
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{ f1 * f2 };
    f3.print();

    Fraction f4{ f1 * 2 };
    f4.print();

    Fraction f5{ 2 * f2 };
    f5.print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    Fraction f7{0, 6};
    f7.print();


    return 0;
}
