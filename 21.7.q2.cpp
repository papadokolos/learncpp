#include <algorithm>
#include <format>
#include <iostream>
#include <print>
#include <string>
#include <string_view>
#include <vector>


namespace V1
{
    class Car
    {
    private:
        std::string m_make{};
        std::string m_model{};

    public:
        Car(std::string_view make, std::string_view model)
            : m_make{ make }, m_model{ model }
        {
        }

        friend bool operator== (const Car& c1, const Car& c2);
        friend bool operator!= (const Car& c1, const Car& c2);

        friend bool operator<(const Car& lhs, const Car& rhs);
        friend std::ostream& operator<<(std::ostream& out, const Car& car);
    };

    bool operator== (const Car& c1, const Car& c2)
    {
        return (c1.m_make == c2.m_make &&
                c1.m_model == c2.m_model);
    }

    bool operator!= (const Car& c1, const Car& c2)
    {
        return (c1.m_make != c2.m_make ||
                c1.m_model != c2.m_model);
    }

    bool operator<(const Car& lhs, const Car& rhs)
    {
        return (lhs.m_make < rhs.m_make)
            || ((lhs.m_make == rhs.m_make) && (lhs.m_model < rhs.m_model));
    }

    std::ostream& operator<<(std::ostream& out, const Car& car)
    {
        out << "(" << car.m_make << ", " << car.m_model << ")";

        return out;
    }
}

inline namespace V2
{
    class Car
    {
    private:
        std::string m_make{};
        std::string m_model{};

    public:
        Car(std::string_view make, std::string_view model)
            : m_make{ make }, m_model{ model }
        {
        }

        auto operator<=>(const Car& other) const = default;
        friend struct std::formatter<Car>;
    };
}

// For V2
template <>
struct std::formatter<V2::Car>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(V2::Car car, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(), "({}, {})", car.m_make, car.m_model
            )
        );

        return ctx.out();
    }
};


int main()
{
  std::vector<Car> cars{
    { "Toyota", "Corolla" },
    { "Honda", "Accord" },
    { "Toyota", "Camry" },
    { "Honda", "Civic" }
  };

  std::sort(cars.begin(), cars.end()); // requires an overloaded operator<

// For V1
/*
  for (const auto& car : cars)
    std::cout << car << '\n'; // requires an overloaded operator<<
*/

// For V2
  // Requested output with newline per value, but this requires std::join_with
  // which is implemented in clang 21 which is yet to be released (first release
  // candidate branch on llvm repo expected on 15 July:
  // - https://discourse.llvm.org/t/llvm-21-x-release-information-and-branching/87065
  // - https://github.com/llvm/llvm-project/milestone/27 )
  // (it is available in GCC though)
  std::println("{:n}", cars);

  return 0;
}
