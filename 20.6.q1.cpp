#include <algorithm>
#include <array>
#include <print>
#include <string>

struct Student
{
    std::string name{};
    int points{};
};


int main(int /*argc*/, char const */*argv*/[])
{
    std::array<Student, 8> arr{
      { { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 }, // Dan has the most points (8).
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 } }
    };

    constexpr auto compareStudentsByPoints{
        [](const Student& a, const Student& b)
        {
            return a.points < b.points;
        }
    };

    const auto pBestStudent{
        std::ranges::max_element(arr, compareStudentsByPoints)
    };

    std::println("{} is the best student.", pBestStudent->name);

    return 0;
}
