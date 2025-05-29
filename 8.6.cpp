#include <iostream>
#include <print>


// Write a function called calculate() that takes two integers and a char representing one of the following mathematical operations: +, -, *, /, or % (remainder). Use a switch statement to perform the appropriate mathematical operation on the integers, and return the result. If an invalid operator is passed into the function, the function should print an error message. For the division operator, do an integer division, and don’t worry about divide by zero.
int calculate(int lhs, int rhs, char op)
{
    switch (op)
    {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        return lhs / rhs;
    case '%':
        return lhs % rhs;
    default:
        std::println("Operator {} is invalid", op);
        return 0;
    }
}

int main(int /*argc*/, char const */*argv*/[])
{
    std::print("Enter first number: ");
    int lhs{};
    std::cin >> lhs;

    std::print("Enter second number: ");
    int rhs{};
    std::cin >> rhs;

    std::print("Enter operator: ");
    char op{};
    std::cin >> op;

    int result{ calculate(lhs, rhs, op) };
    std::println("Result: {}", result);

    return 0;
}