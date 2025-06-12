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

    for (std::size_t index{ 0 }; index < arr.size(); ++index)
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


int main(int /*argc*/, char const */*argv*/[])
{
    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };

    printMinAndMax(v1);
    std::println();
    printMinAndMax(v2);
    
    return 0;
}