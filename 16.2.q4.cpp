#include "CInTools.h"

#include <print>
#include <vector>


std::vector<int> getIntegersFromCLI(std::vector<int>::size_type numIntegers)
{
    // Create a value-initialized vector of length `numIntegers`
    std::vector<int> integers(numIntegers);

    while (true)
    {
        std::print("{}", "Enter 3 integers: ");
        std::cin >> integers[0] >> integers[1] >> integers[2];

        if (clearFailedExtraction())
        {
            continue;
        }
        if (hasUnextractedInput())
        {
            ignoreLine();
            continue;
        }
 
        return integers;
    }
}


int main(int /*argc*/, char const */*argv*/[])
{
    std::vector<int> integers{ getIntegersFromCLI(3) };

    std::println("The sum is: {}",     integers[0] + integers[1] + integers[2]);
    std::println("The product is: {}", integers[0] * integers[1] * integers[2]);

    return 0;
}