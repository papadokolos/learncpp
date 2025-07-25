#include <cstdint>
#include <print>
#include <iostream>


/**
 * Calculate average over a summation of numbers.
 * Sum is bounded to 32 bit integer representation.
 */
class Average
{
public:
    /* Rule of zero (default implementations suffice) */

    Average& operator+=(int num);

    double get() const;

private:
    std::int32_t m_sum{ 0 };
    int m_numSummedNums{ 0 };
};

Average& Average::operator+=(int num)
{
    m_sum += num;
    ++m_numSummedNums;

    return *this;
}

double Average::get() const
{
    return (m_numSummedNums == 0)  // Avoid zero division
    ? 0
    : (static_cast<double>(m_sum) / m_numSummedNums);
}

/********************************************************************
  Output support (std::ostream, std::format)
********************************************************************/
template <>
struct std::formatter<Average>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(const Average& avg, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(), "{}", avg.get()
            )
        );

        return ctx.out();
    }
};

std::ostream& operator<<(std::ostream& out, const Average& avg)
{
    out << std::format("{}", avg);

    return out;
}


int main()
{
    Average avg{};
    std::cout << avg << '\n';

    avg += 4;
    std::cout << avg << '\n'; // 4 / 1 = 4

    avg += 8;
    std::cout << avg << '\n'; // (4 + 8) / 2 = 6

    avg += 24;
    std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

    avg += -10;
    std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

    (avg += 6) += 10; // 2 calls chained together
    std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

    Average copy{ avg };
    std::cout << copy << '\n';

    return 0;
}
