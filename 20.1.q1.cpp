#include "CInTools.h"

#include <functional>
#include <print>


using ArithmeticFunction = std::function<int (int, int)>;

namespace Operator
{
    // Use fixed type to allow safe casting from `char` of any value:
    // https://stackoverflow.com/questions/33812998/is-it-allowed-for-an-enum-to-have-an-unlisted-value
    enum Type : char
    {
        addition = '+',
        subtraction = '-',
        multiplication = '*',
        division = '/',
    };

    Type getFromCLI()
    {
        while (true)
        {
            const char input{ Input::get<char>("Enter operator (+, -, *, /): ") };

            // "Casting" to enum type so the compiler warns for missing values in
            // switch (e.g. if adding support for additional operators).
            // In case `input` contains an invalid value, it's not undefined
            // behavior, as explained above.
            const Type op{ input };

            switch (op)
            {
            case addition:
            case subtraction:
            case multiplication:
            case division:
                return op;
            }
        }
    }
}

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    if (b == 0)
    {
        return 0; // Better print an error, but for now just avoid UB
    }

    return a / b;
}

ArithmeticFunction getArithmeticFunction(Operator::Type op)
{
    switch (op)
    {
    using enum Operator::Type;
    case addition:       return &add;
    case subtraction:    return &subtract;
    case multiplication: return &multiply;
    case division:       return &divide;
    }
}


int main(int /*argc*/, char const */*argv*/[])
{
    int operand1{ Input::get<int>("Enter first operand: ") };
    int operand2{ Input::get<int>("Enter second operand: ") };

    Operator::Type op{ Operator::getFromCLI() };
    auto operatorFunc{ getArithmeticFunction(op) };

    int result{ operatorFunc(operand1, operand2) };
    std::println("= {}", result);


    return 0;
}
