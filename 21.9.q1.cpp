#include <algorithm>
#include <functional>
#include <print>
#include <string>
#include <string_view>
#include <vector>


struct StudentGrade
{
    std::string name{};
    char grade{};
};

class GradeMap
{
public:
    char& operator[](const std::string& name);

private:
    StudentGrade& findOrCreate(const std::string& name);

    std::vector<StudentGrade> m_map{};
};

StudentGrade& GradeMap::findOrCreate(const std::string& name)
{
    auto findResult{ std::ranges::find(m_map, name, &StudentGrade::name) };
    return findResult != m_map.end()
        ? *findResult
        : m_map.emplace_back(name);
}

char& GradeMap::operator[](const std::string& name)
{
    return findOrCreate(name).grade;
}

int main(int /*argc*/, char const */*argv*/[])
{

    return 0;
}
