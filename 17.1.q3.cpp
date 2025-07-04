#include <array>
#include <print>


int main(int /*argc*/, char const */*argv*/[])
{
    std::array arr{ 'h','e','l','l','o' };

    std::println("{}", arr[1]);

    return 0;
}