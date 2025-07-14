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
    Apple(std::string_view color) : Apple("apple", color) {}

protected:
    Apple(std::string_view name, std::string_view color) : Fruit(name, color) {}
};

class Banana : public Fruit
{
public:
    Banana() : Fruit("banana", "yellow") {}
};

class GrannySmith : public Apple
{
public:
    GrannySmith() : Apple("granny smith apple", "green") {}
};


int main(int /*argc*/, char const */*argv*/[])
{
    Apple a{ "red" };
    Banana b;
    GrannySmith c;

    std::println("My {} is {}.", a.getName(), a.getColor());
    std::println("My {} is {}.", b.getName(), b.getColor());
    std::println("My {} is {}.", c.getName(), c.getColor());

    return 0;
}
