#include <iostream>
#include <iterator>
#include <utility>

int main()
{
    int array[]{ 30, 50, 20, 10, 40 };
    constexpr int length{ static_cast<int>(std::size(array)) };

    // Step through each element of the array
    // (except the last one, which will already be sorted by the time we get there)
    for (int startIndex{ 0 }; startIndex < length - 1; ++startIndex)
    {
        // biggest is the index of the biggest element we’ve encountered this iteration
        // Start by assuming the biggest element is the first element of this iteration
        int biggest{ startIndex };

        // Then look for a bigger element in the rest of the array
        for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex)
        {
            // If we've found an element that is bigger than our previously found biggest
            if (array[currentIndex] > array[biggest])
                // then keep track of it
                biggest = currentIndex;
        }

        // biggest is now the index of the biggest element in the remaining array
                // swap our start element with our biggest element (this sorts it into the correct place)
        std::swap(array[startIndex], array[biggest]);
    }

    // Now that the whole array is sorted, print our sorted array as proof it works
    for (int index{ 0 }; index < length; ++index)
        std::cout << array[index] << ' ';

    std::cout << '\n';

    return 0;
}
