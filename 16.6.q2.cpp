#include <print>
#include <vector>
#include <cstddef>

template <typename T>
void printArray(const std::vector<T>& arr)
{
    // Only in next chapter we discuss alternatives to std::size_t
    for (std::size_t i{ 0 }; i < arr.size(); ++i)
    {
        std::print("{} ", arr[i]);
    }
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
    printArray(arr);

    return 0;
}