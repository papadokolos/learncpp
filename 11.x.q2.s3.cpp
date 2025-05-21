#include <iostream>

namespace V1
{
    template <typename T, typename U>
    auto sub(T x, U y) -> std::common_type_t<T, U> // The -> part is just for readability.
    {
        return x - y;
    }
}

inline namespace V2
{
    auto sub(auto x, auto y)
    {
        return x - y;
    }
}

int main()
{
    std::cout << sub(3, 2) << '\n';
    std::cout << sub(3.5, 2) << '\n';
    std::cout << sub(4, 1.5) << '\n';

    std::cout << V1::sub(3, 2) << '\n';
    std::cout << V1::sub(3.5, 2) << '\n';
    std::cout << V1::sub(4, 1.5) << '\n';

    return 0;
}