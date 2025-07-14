#include <format>
#include <print>
#include <string>
#include <string_view>


class Fruit
{
public:
    Fruit(std::string_view name, std::string_view color);

    auto getName() const -> const std::string& { return m_name; }
    auto getColor() const -> const std::string& { return m_color; }

private:
    std::string m_name{};
    std::string m_color{};
};

Fruit::Fruit(std::string_view name, std::string_view color)
    : m_name{ name }
    , m_color{ color }
{}

class Apple : public Fruit
{
public:
    Apple(std::string_view name, std::string_view color, double fiber);

    auto getFiber() const { return m_fiber; }

private:
    double m_fiber{};
};

Apple::Apple(std::string_view name, std::string_view color, double fiber)
    : Fruit(name, color)
    , m_fiber{ fiber }
{}

class Banana : public Fruit
{
public:
    Banana(std::string_view name, std::string_view color);
};

Banana::Banana(std::string_view name, std::string_view color)
    : Fruit(name, color)
{}


template <>
struct std::formatter<Fruit>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(const Fruit& fruit, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(), "Fruit({}, {})", fruit.getName(), fruit.getColor()
            )
        );

        return ctx.out();
    }
};

template <>
struct std::formatter<Apple>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(const Apple& apple, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(),
                "Apple({}, {}, {})",
                apple.getName(),
                apple.getColor(),
                apple.getFiber()
            )
        );

        return ctx.out();
    }
};

template <>
struct std::formatter<Banana>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(const Banana& banana, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(), "Banana({}, {})", banana.getName(), banana.getColor()
            )
        );

        return ctx.out();
    }
};


int main(int /*argc*/, char const */*argv*/[])
{
    const Apple a{ "Red delicious", "red", 4.2 };
    std::println("{}", a);

    const Banana b{ "Cavendish", "yellow" };
    std::println("{}", b);

    return 0;
}
