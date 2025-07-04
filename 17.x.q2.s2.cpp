#include "Random.h"
#include "CInTools.h"

#include <array>
#include <cassert>
#include <cctype>
#include <optional>
#include <print>
#include <source_location>
#include <string_view>
#include <utility>
#include <variant>


namespace Potion
{
    constexpr int enumStart{ std::source_location::current().line() };
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,
    };
    constexpr int enumEnd{ std::source_location::current().line() };
    constexpr int extraLines{ 4 };
    constexpr int numTypes{ enumEnd - enumStart - extraLines };

    constexpr std::array types{ healing, mana, speed, invisibility };
    static_assert(types.size() == numTypes);

    constexpr std::array costPerType{ 20, 30, 12, 50 };
    static_assert(costPerType.size() == numTypes);

    using namespace std::string_view_literals;
    constexpr std::array namePerType{ std::to_array<std::string_view>({
        "healing", "mana", "speed", "invisibility" })
    };
    static_assert(namePerType.size() == numTypes);
}

class InvalidValue
{
public:
    template <typename T>
    operator T()
    {
        static_assert(false, "Initializing with invalid value");
    }
};

class Player
{
public:
    explicit Player(std::string_view name) : m_name(name)
    {}

    const std::string& getName() const { return m_name; }

    int getGold() const { return m_gold; }

private:
    static constexpr int s_minStartGold{ 80 };
    static constexpr int s_maxStartGold{ 120 };

    std::string m_name{ InvalidValue() };
    std::array<int, Potion::numTypes> m_inventory{ 0, 0, 0, 0 };
    int m_gold{ Random::get(s_minStartGold, s_maxStartGold) };
};


void shop()
{
    std::println("Here is our selection for today:");
    for (auto potionType : Potion::types)
    {
        std::println(
            "{}) {} costs {}",
            static_cast<int>(potionType),
            Potion::namePerType[potionType],
            Potion::costPerType[potionType]);
    }
}


int main(int /*argc*/, char const */*argv*/[])
{
    std::println("Welcome to Roscoe's potion emporium!");
    const std::string name{ Input::get<std::string>("Enter your name: ") };

    Player player{ name };
    std::println(
        "Hello {}, you have {} gold.",
        player.getName(),
        player.getGold());
    std::println();

    shop();
    std::println();
    std::println("Thanks for shopping at Roscoe's potion emporium!");

    return 0;
}
