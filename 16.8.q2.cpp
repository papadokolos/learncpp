#include "CInTools.h"

#include <print>
#include <string>
#include <string_view>
#include <vector>


template <typename T>
bool isValueInArray(const std::vector<T>& arr, const T& val)
{
    for (const auto& elem : arr)
    {
        if (elem == val)
        {
            return true;
        }
    }

    return false;
}


int main(int /*argc*/, char const */*argv*/[])
{
    const std::vector<std::string_view> names{
        "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };

    std::string nameFromUser{ Input::get<std::string>("Enter a name: ") };

    // (Template Argument Deduction disallows casting, hence explicit type used)
    if (isValueInArray<std::string_view>(names, nameFromUser))
    {
        std::println("{} was found.", nameFromUser);
    }
    else
    {
        std::println("{} was not found.", nameFromUser);
    }

    return 0;
}