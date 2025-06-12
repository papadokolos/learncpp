#include <cassert>
#include <print>
#include <source_location>
#include <string_view>
#include <vector>


namespace Items
{
    constexpr auto beforeEnum{ std::source_location::current().line() };
    enum Type
    {
        healthPotion,
        torch,
        arrow,
    };
    constexpr auto afterEnum{ std::source_location::current().line() };
    constexpr int overheadLines{ 4 };
    constexpr int numTypes{ afterEnum - beforeEnum - overheadLines };

    std::string_view toSingularString(Type itemType)
    {
        switch (itemType)
        {
        case healthPotion: return "health potion";
        case torch: return "torch";
        case arrow: return "arrow";
        }

        return "???";
    }

    std::string_view toPluralString(Type itemType)
    {
        switch (itemType)
        {
        case healthPotion: return "health potions";
        case torch: return "torches";
        case arrow: return "arrows";
        }

        return "???";
    }
}

std::string_view getItemName(Items::Type type, int itemCount)
{
    return (itemCount == 1) ?
        Items::toSingularString(type) : Items::toPluralString(type);
}

void printItemCount(const std::vector<int>& itemsPerType)
{
    int totalItems{ 0 };
    for (std::size_t index{ 0 }; index < itemsPerType.size(); ++index)
    {
        int items{ itemsPerType[index] };
        Items::Type itemType{ static_cast<Items::Type>(index) };
        std::println("You have {} {}", items, getItemName(itemType, items));

        totalItems += items;
    }

    std::println("You have {} total items", totalItems);
}


int main(int /*argc*/, char const */*argv*/[])
{
    std::vector<int> itemsPerType{ 1, 5, 10 };
    assert(itemsPerType.size() == Items::numTypes);

    printItemCount(itemsPerType);

    return 0;
}