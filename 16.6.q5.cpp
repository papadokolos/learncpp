#include <iostream>
#include <vector> // For std::vector, std::size_t

template <typename T>
T findMax(const std::vector<T>& arr)
{
    if (arr.empty())
    {
        return T{};
    }

    std::size_t indexOfMax{ 0 };
    for (std::size_t index{ 1 }; index < arr.size(); ++index)
    {
        if (arr[index] > arr[indexOfMax])
        {
            indexOfMax = index;
        }
    }

    return arr[indexOfMax];
}


int main()
{
    std::vector data1 { 84, 92, 76, 81, 56 };
    std::cout << findMax(data1) << '\n';

    std::vector data2 { -13.0, -26.7, -105.5, -14.8 };
    std::cout << findMax(data2) << '\n';

    std::vector<int> data3 { };
    std::cout << findMax(data3) << '\n';

    return 0;
}