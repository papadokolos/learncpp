#include <print>
#include <format> // For specializing print to custom type

#include "CInTools.h"


struct Fraction
{
    int numerator { 0 };
    int denominator { 1 };
};

Fraction getFractionFromCLI()
{
    return {
        .numerator{ getInputFromUser<int>("Enter numerator: ") },
        .denominator{ getInputFromUser<int>("Enter denominator: ") }
    };
}

// Since Fraction is small, we pass by value:
// (sizeof(Fraction) <= 2 "words" of memory == memory address size * 2),
// Chapter 12.6: https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/
constexpr Fraction multiplyFractions(Fraction a, Fraction b)
{
    return {
        .numerator { a.numerator * b.numerator },
        .denominator { a.denominator * b.denominator }
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
                ctx.out(), "{}/{}", fraction.numerator, fraction.denominator
            )
        );

        return ctx.out();
    }
};


int main(int /*argc*/, char const */*argv*/[])
{
    Fraction fraction1 { getFractionFromCLI() };

    std::println(); // Line separate input in CLI
    Fraction fraction2 { getFractionFromCLI() };

    Fraction multiple { multiplyFractions(fraction1, fraction2) };

    std::println(); // Line separate input in CLI
    std::println("Your fractions multiplied together: {}", multiple);

    return 0;
}