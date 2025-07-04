#include <array>
#include <print>


int main(int /*argc*/, char const */*argv*/[])
{
    std::array arr{ 'h','e','l','l','o' };

    std::println("{}{}{}", arr[1], arr.at(1), std::get<1>(arr));

    return 0;
}