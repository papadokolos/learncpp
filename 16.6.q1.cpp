#include <print>
#include <vector>
#include <cstddef>

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    // Only in next chapter we discuss alternatives to std::size_t
    for (std::size_t i{ 0 }; i < std::size(arr); ++i)
    {
        std::print("{} ", arr[i]);
    }

    return 0;
}