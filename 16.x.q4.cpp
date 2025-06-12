#include "CInTools.h"

#include <cstddef>
#include <print>
#include <utility>
#include <vector>


template <typename T>
std::pair<std::size_t, std::size_t> findMinAndMaxIndices(
    const std::vector<T>& arr)
{
    std::size_t indexMin{ 0 };
    std::size_t indexMax{ 0 };

    for (std::size_t index{ 1 }; index < arr.size(); ++index)
    {
        if (arr[index] < arr[indexMin])
        {
            indexMin = index;
        }
        else if (arr[index] > arr[indexMax])
        {
            indexMax = index;
        }
    }

    return { indexMin, indexMax };
}

template <typename T>
void printMinAndMax(
    const std::vector<T>& arr)
{
    if (arr.empty())
    {
        std::println("With empty array there are no min and max elements.");
        return;
    }

    auto [indexMin, indexMax]{ findMinAndMaxIndices(arr) };

    std::println("With array {}:", arr);
    std::println(
        "The min element has index {} and value {}",
        indexMin,
        arr[indexMin]);
    std::println(
        "The max element has index {} and value {}",
        indexMax,
        arr[indexMax]);
}


std::vector<int> getVectorFromCLI()
{
    constexpr int inputEndSentinel{ -1 };
    std::vector<int> numbers{};

    std::print("Enter numbers to add (use -1 to stop): ");

    while (true)
    {
        int number{ Input::get<int>(
            "",
            { .ignoreExtraneousInput{ true }
            , .removeExtraneousInput{ false } }
        ) };

        if (number == inputEndSentinel)
        {
            return numbers;
        }

        numbers.push_back(number);
    }
}


int main(int /*argc*/, char const */*argv*/[])
{
    std::vector<int> numbers{ getVectorFromCLI() };

    printMinAndMax(numbers);
    
    return 0;
}