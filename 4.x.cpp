#include <iostream>


double get_operand_input()
{
    std::print("Enter a double value: ");

    double operand {};
    std::cin >> operand;

    return operand;
}

char get_operator_input()
{
    std::print("Enter +, -, *, or /: ");

    char op {};
    std::cin >> op;

    return op;
}

double calculate(double x, double y, char op)
{
    switch(op)
    {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        default: // Invalid op
            return 0;
    }
}

bool is_valid_operator1(char op)
{
    switch(op)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}

template<typename First, typename ... T>
bool is_in(First &&first, T && ... t)
{
    return ((first == t) || ...);
}

bool is_valid_operator2(char op)
{
    return is_in(op, '+', '-', '*', '/');
}


int main(int /*argc*/, char const */*argv*/[])
{
    double x {get_operand_input()};
    double y {get_operand_input()};
    char op {get_operator_input()};

    if (is_valid_operator2(op))
    {
        double result = calculate(x, y, op);
        std::print("{} {} {} is {}", x, op, y, result);
    }


    return 0;
}