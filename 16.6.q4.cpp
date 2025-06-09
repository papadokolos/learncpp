#include "CInTools.h"

#include <optional>
#include <print>
#include <type_traits>
#include <vector>
#include <cstddef>

template <typename T>
T get1to9FromCLI() requires std::is_arithmetic_v<T>
{
    while (true)
    {
        T num{ 
            Input::get<T>(
                "Enter a number between 1 and 9: ",
                { .ignoreExtraneousInput { true } }
            )
        };
        bool num_within_range{ (num >= 1) && (num <= 9) };
        if (num_within_range)
        {
            return num;
        }
    }
}

template <typename T>
void printArray(const std::vector<T>& arr)
{
    // Only in next chapter we discuss alternatives to std::size_t
    for (std::size_t i{ 0 }; i < arr.size(); ++i)
    {
        std::print("{} ", arr[i]);
    }

    std::println();
}

template <typename T>
std::optional<std::size_t> findValueInArray(
    const std::vector<T>& arr, const T& value)
{
    // Only in next chapter we discuss alternatives to std::size_t
    for (std::size_t i{ 0 }; i < arr.size(); ++i)
    {
        if (arr[i] == value)
        {
            return i;
        }
    }

    return std::nullopt;
}

int main()
{
    int num{ get1to9FromCLI<int>() };
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
    printArray(arr);

    // Version 1:
    std::optional<std::size_t> optional_index { findValueInArray(arr, num) };
    if (optional_index)
    {
        std::println("The number {} has index {}", num, *optional_index);
    }
    else
    {
        std::println("The number {} was not found", num);
    }

    std::vector arr2{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };
    double num2{ get1to9FromCLI<double>() };

    // Version 2: Using C++23 Monadic Operations
    findValueInArray(arr2, num2).transform(
        [num2](int index)
        {
            std::println("The number {} has index {}", num2, index);
            return index;
        }
    ).or_else(
        [num2]()
        {
            std::println("The number {} was not found", num2);
            return std::optional{0};
        }
    );


    return 0;
}