#include "CInTools.h"

#include <optional>
#include <print>
#include <vector>
#include <cstddef>

int get1to9FromCLI()
{
    while (true)
    {
        int num{ 
            Input::get<int>(
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
    int num{ get1to9FromCLI() };
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
    printArray(arr);

    // Version 1:
    // std::optional<std::size_t> optional_index { findValueInArray(arr, num) };
    // if (optional_index)
    // {
    //     std::println("The number {} has index {}", num, *optional_index);
    // }
    // else
    // {
    //     std::println("The number {} was not found", num);
    // }
    
    // Version 2: Using C++23 Monadic Operations
    findValueInArray(arr, num).transform(
        [num](int index)
        {
            std::println("The number {} has index {}", num, index);
            return index;
        }
    ).or_else(
        [num]()
        {
            std::println("The number {} was not found", num);
            return std::optional{0};
        }
    );


    return 0;
}