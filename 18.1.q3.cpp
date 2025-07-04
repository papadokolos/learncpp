#include <cctype>
#include <iterator>
#include <print>
#include <utility>


int main(int /*argc*/, char const */*argv*/[])
{
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    std::println("Before: {}", array);

    for (int iteration{ 0 }; iteration < std::ssize(array); ++iteration)
    {
        for (int index{ 1 }; index < std::ssize(array); ++index)
        {
            if (array[index - 1] > array[index])
            {
                std::swap(array[index - 1], array[index]);
            }
        }
    }

    std::println("After:  {}", array);


    return 0;
}
