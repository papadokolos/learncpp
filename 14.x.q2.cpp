#include <print>
#include <format> // For specializing print to custom type

#include "CInTools.h"


class Fraction
{
public:
    static Fraction getFractionFromCLI();

    explicit Fraction(int numerator = 0, int denominator = 1);

    constexpr Fraction multiplyFractions(Fraction other) const;

    friend std::formatter<Fraction>;

private:
    int m_numerator { 0 };
    int m_denominator { 1 };
};

Fraction Fraction::getFractionFromCLI()
{
    return Fraction{
        getInputFromUser<int>("Enter numerator: "),
        getInputFromUser<int>("Enter denominator: ")
    };
}

Fraction::Fraction(int numerator, int denominator)
    : m_numerator(numerator), m_denominator(denominator)
{}

constexpr Fraction Fraction::multiplyFractions(Fraction other) const
{
    return Fraction{
        m_numerator * other.m_numerator,
        m_denominator * other.m_denominator
    };
}

// Enabling printing of Fraction via std::print (see 13.10.q1.cpp)
template <>
struct std::formatter<Fraction>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(Fraction fraction, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(), "{}/{}", fraction.m_numerator, fraction.m_denominator
            )
        );

        return ctx.out();
    }
};


int main(int /*argc*/, char const */*argv*/[])
{
    Fraction fraction1 { Fraction::getFractionFromCLI() };

    std::println(); // Line separate input in CLI
    Fraction fraction2 { Fraction::getFractionFromCLI() };

    Fraction multiple { fraction1.multiplyFractions(fraction2) };

    std::println(); // Line separate input in CLI
    std::println("Your fractions multiplied together: {}", multiple);

    return 0;
}