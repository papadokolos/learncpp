#include <print>
#include <array>
#include <string_view>


struct Item
{
    std::string_view name{};
    int gold{};
};

int main(int /*argc*/, char const */*argv*/[])
{
    std::array<Item, 4> items{{
        { "sword", 5 },
        { "dagger", 3 },
        { "club", 2 },
        { "spear", 7 }
    }};

    for (const auto& item : items)
    {
        std::println("A {} costs {} gold.", item.name, item.gold);
    }

    return 0;
}