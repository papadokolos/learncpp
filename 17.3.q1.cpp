#include <array>
#include <cstddef>
#include <print>


template <typename T, std::size_t N>
void printArray(const std::array<T, N>& arr)
{
    std::println("The array {} has length {}", arr, N);
}

int main(int /*argc*/, char const */*argv*/[])
{
    constexpr std::array arr1 { 1, 4, 9, 16 };
    printArray(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr2);

    return 0;
}