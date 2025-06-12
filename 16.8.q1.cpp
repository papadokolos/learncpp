#include "CInTools.h"

#include <print>
#include <string>
#include <string_view>
#include <vector>




int main(int /*argc*/, char const */*argv*/[])
{
    const std::vector<std::string_view> names{
        "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };

    std::string nameFromUser{ Input::get<std::string>("Enter a name: ") };

    bool found{ false };
    for (std::string_view name : names) // Better explicitly use string_view
    {
        if (nameFromUser == name)
        {
            found = true;
            break;
        }
    }
    
    if (found)
    {
        std::println("{} was found.", nameFromUser);
    }
    else
    {
        std::println("{} was not found.", nameFromUser);
    }

    return 0;
}