#include <print>
#include <string_view>
#include <vector>



int main(int /*argc*/, char const */*argv*/[])
{
    std::vector a{ 2, 4, 6, 8, 10, 12 };

    const std::vector b{ 1.2, 3.4, 5.6, 7.8 };

    using namespace std::string_view_literals;
    const std::vector c{ "Alex"sv, "Brad"sv, "Charles"sv, "Dave"sv };

    std::vector d{ 12 };

    std::vector<int> e(12);

    return 0;
}