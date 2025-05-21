// Make sure that assert triggers even if we compile in release mode
#undef NDEBUG

#include <cassert> // for assert
#include <iostream>
#include <cmath>


namespace V1
{
    bool isPrime(int x)
    {
        if (!(x > 1))
        {
            return false;
        }

        for (int number{ 2 }; number < x; ++number)
        {
            if (x % number == 0)
            {
                return false;
            }
        }

        return true;
    }    
}

inline namespace V2 // Solution for Extra credit part
{
    bool isPrime(int x)
    {
        if (!(x > 1))
        {
            return false;
        }

        if (x != 2 && x % 2 == 0)
        {
            return false;
        }

        // Test uneven values up to sqrt(x) (conditional is squared)
        for (int number{ 3 }; number * number <= x; number += 2)
        {
            if (x % number == 0)
            {
                return false;
            }
        }

        return true;
    }
}


int main()
{
    assert(!isPrime(0)); // terminate program if isPrime(0) is true
    assert(!isPrime(1));
    assert(isPrime(2));  // terminate program if isPrime(2) is false
    assert(isPrime(3));
    assert(!isPrime(4));
    assert(isPrime(5));
    assert(isPrime(7));
    assert(!isPrime(9));
    assert(isPrime(11));
    assert(isPrime(13));
    assert(!isPrime(15));
    assert(!isPrime(16));
    assert(isPrime(17));
    assert(isPrime(19));
    assert(isPrime(97));
    assert(!isPrime(99));
    assert(isPrime(13417));

    std::cout << "Success!\n";

    return 0;
}