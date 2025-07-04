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
    std::array items{ 
        Item{ "sword", 5 },
        Item{ "dagger", 3 },
        Item{ "club", 2 },
        Item{ "spear", 7 }
    };

    for (const auto& item : items)
    {
        std::println("A {} costs {} gold.", item.name, item.gold);
    }

    return 0;
}