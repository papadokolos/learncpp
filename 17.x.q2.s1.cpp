#include <array>
#include <print>
#include <source_location>
#include <string_view>


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
    shop();

    return 0;
}
