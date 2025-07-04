#include <cctype>
#include <iterator>
#include <print>
#include <utility>


int main(int /*argc*/, char const */*argv*/[])
{
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    std::println("Before: {}", array);

    for (int iteration{ 1 }; iteration < std::ssize(array); ++iteration)
    {
        bool elementsWereSwapped{ false };

        const auto lastUnsortedIndex{ std::ssize(array) - iteration - 1 };
        for (int index{ 1 }; index <= lastUnsortedIndex; ++index)
        {
            if (array[index - 1] > array[index])
            {
                std::swap(array[index - 1], array[index]);
                elementsWereSwapped = true;
            }
        }

        if (bool arrayIsSorted{ !elementsWereSwapped }; arrayIsSorted)
        {
            std::println("Early termination on iteration {}", iteration);
            break;
        }
    }

    std::println("After:  {}", array);


    return 0;
}
