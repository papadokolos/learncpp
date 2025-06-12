#include <print>
#include <vector>


template <typename T>
void printStack(const std::vector<T>& arr)
{
    std::print("(Stack:");

    if (arr.empty())
    {
        std::print(" empty");
    }
    /*else*/ for (const T& elem : arr)
    {
        std::print(" {}", elem);
    }

    std::println(")");
}

template <typename T>
void popFromArrayAndPrint(std::vector<T>& arr)
{
    arr.pop_back();

    std::print("Pop\t");
    printStack(arr);
}

template <typename T>
void pushToArrayAndPrint(std::vector<T>& arr, T&& value)
{
    arr.push_back(value);

    std::print("Push {}\t", value);
    printStack(arr);
}


int main(int /*argc*/, char const */*argv*/[])
{
    std::vector<int> numbers{};
    printStack(numbers);

    pushToArrayAndPrint(numbers, 1);
    pushToArrayAndPrint(numbers, 2);
    pushToArrayAndPrint(numbers, 3);
    popFromArrayAndPrint(numbers);
    pushToArrayAndPrint(numbers, 4);
    popFromArrayAndPrint(numbers);
    popFromArrayAndPrint(numbers);
    popFromArrayAndPrint(numbers);

    return 0;
}