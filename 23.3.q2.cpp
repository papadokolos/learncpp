#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>


class Teacher
{
private:
  std::string m_name{};

public:
  explicit Teacher(std::string_view name)
      : m_name{ name }
  {
  }

  const std::string& getName() const { return m_name; }
};

class Department
{
private:
  std::vector<std::reference_wrapper<const Teacher>> m_teachers{};

public:
  Department() = default;

  void add(const Teacher& teacher);

  friend struct std::formatter<Department>;
};

void Department::add(const Teacher& teacher)
{
    m_teachers.emplace_back(teacher);
}

/********************************************************************
  Output support (std::ostream, std::format)
********************************************************************/
// For both Teacher and std::reference_wrapper<Teacher>
template <typename T>
    requires std::is_convertible_v<T, Teacher>
struct std::formatter<T>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(const Teacher& teacher, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(), "{}", teacher.getName()
            )
        );

        return ctx.out();
    }
};

template <>
struct std::formatter<Department>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(const Department& department, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(), "Department: {:n}", department.m_teachers
            )
        );

        return ctx.out();
    }
};

std::ostream& operator<<(std::ostream& out, const Teacher& teacher)
{
    out << std::format("{}", teacher);

    return out;
}

std::ostream& operator<<(std::ostream& out, const Department& department)
{
    out << std::format("{}", department);

    return out;
}


int main()
{
  // Create a teacher outside the scope of the Department
  Teacher t1{ "Bob" };
  Teacher t2{ "Frank" };
  Teacher t3{ "Beth" };

  {
    // Create a department and add some Teachers to it
    Department department{}; // create an empty Department

    department.add(t1);
    department.add(t2);
    department.add(t3);

    std::cout << department << "\n";

  } // department goes out of scope here and is destroyed

  std::cout << t1.getName() << " still exists!\n";
  std::cout << t2.getName() << " still exists!\n";
  std::cout << t3.getName() << " still exists!\n";

  return 0;
}
