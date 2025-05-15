#include <iostream>
#include <istream>
#include <string>
#include <string_view>

std::string getNameFromCLI()
{
    static int person_index = 0;
    ++person_index;

    std::println("Enter the name of person #{}: ", person_index);
    std::string name{};
    std::getline(std::cin >> std::ws, name);

    return name;
}

int getAgeFromCLI(std::string_view name)
{
    std::println("Enter the age of {}: ", name);
    int age{};
    std::cin >> age;

    return age;
}

void printAgeComparison(int age1, std::string_view name1, int age2, std::string_view name2)
{
    int older_age {age1};
    std::string_view older_name {name1};
    int younger_age {age2};
    std::string_view younger_name {name2};

    if (age1 < age2)
    {
        older_age = age2;
        older_name = name2;
        younger_age = age1;
        younger_name = name1;
    }

    std::println("{} (age {}) is older than {} (age {}).",
        older_name, older_age, younger_name, younger_age);
}

int main()
{
    const std::string p1_name{ getNameFromCLI() };
    const int p1_age{ getAgeFromCLI(p1_name) };

    const std::string p2_name{ getNameFromCLI() };
    const int p2_age{ getAgeFromCLI(p2_name) };

    printAgeComparison(p1_age, p1_name, p2_age, p2_name);

    return 0;
}