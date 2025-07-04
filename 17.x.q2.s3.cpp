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
    bool payGold(int amount);

    int getInventory(Potion::Type potionType) const
        { return m_inventory[potionType]; }
    // Negative `amount` is ignored
    void setInventory(Potion::Type potionType, int amount);

private:
    static constexpr int s_minStartGold{ 80 };
    static constexpr int s_maxStartGold{ 120 };

    std::string m_name{ InvalidValue() };
    std::array<int, Potion::numTypes> m_inventory{ 0, 0, 0, 0 };
    int m_gold{ Random::get(s_minStartGold, s_maxStartGold) };
};

bool Player::payGold(int amount)
{
    if (getGold() >= amount)
    {
        m_gold -= amount;
        return true;
    }

    return false;
}

void Player::setInventory(Potion::Type potionType, int amount)
{
    if (amount >= 0)
    {
        m_inventory[potionType] = amount;
    }
}


namespace Shop
{
    constexpr char quitChar{ 'q' };
    constexpr std::string_view selection{
        "Here is our selection for today:"
    };
    constexpr std::string_view purchaseInstructions{
        "Enter the number of the potion you'd like to buy, or 'q' to quit: "
    };
    constexpr std::string_view purchaseComplete{
        "You purchased a potion of {}.  You have {} gold left."
    };
    constexpr std::string_view purchaseTooExpensive{
        "You can not afford that."
    };
    constexpr std::string_view invalidInput{
        "That is an invalid input.  Try again: "
    };

    namespace { // Internal linkage (just for good practice)
    namespace Helper
    {
        void printSelection()
        {
            std::println(selection);
            for (auto potionType : Potion::types)
            {
                std::println(
                    "{}) {} costs {}",
                    static_cast<int>(potionType),
                    Potion::namePerType[potionType],
                    Potion::costPerType[potionType]);
            }
        }

        constexpr int toInt(char letter)
        {
            return letter - '0';
        }

        constexpr std::optional<Potion::Type> toPotionType(char letter)
        {
            // Cast to have compiler warning on missing enum values in switch
            auto potionType{ static_cast<Potion::Type>(toInt(letter)) };
            switch (potionType)
            {
            case Potion::healing:
            case Potion::mana:
            case Potion::speed:
            case Potion::invisibility:
                return std::make_optional(potionType);
            }

            return std::nullopt;
        }

        void handlePurchase(Potion::Type potionType, Player& player)
        {
            if (player.payGold(Potion::costPerType[potionType]))
            {
                player.setInventory(
                    potionType, player.getInventory(potionType) + 1);
                std::println(
                    purchaseComplete,
                    Potion::namePerType[potionType],
                    player.getGold());
            }
            else
            {
                std::println(purchaseTooExpensive);
            }
        }

        using QuitShop = std::monostate;
        using InputVariant = std::variant<QuitShop, Potion::Type>;
        InputVariant handleInput()
        {
            std::print(purchaseInstructions);

            while (true)
            {
                const char input{ Input::get<char>("") };
                if (input == quitChar)
                {
                    return InputVariant{ std::in_place_type<QuitShop> };
                }

                const auto result{ toPotionType(input) };
                if (result)
                {
                    return InputVariant{
                        std::in_place_type<Potion::Type>, *result
                    };
                }

                std::print(invalidInput);
            }
        }
    }}

    void shop(Player& player)
    {
        using namespace Helper;

        while (true)
        {
            printSelection();

            const auto result{ handleInput() };
            if (std::holds_alternative<QuitShop>(result))
            {
                return;
            }

            assert(std::holds_alternative<Potion::Type>(result));
            const auto potionType{ std::get<Potion::Type>(result) };
            handlePurchase(potionType, player);

            std::println();
        }
    }
}

void printInventory(const Player& player)
{
    std::println("Your inventory contains:");
    for (auto potionType : Potion::types)
    {
        const int potionCount{ player.getInventory(potionType) };
        if (potionCount <= 0)
        {
            continue;
        }

        std::println(
            "{}x potion of {}",
            potionCount,
            Potion::namePerType[potionType]
        );
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

    Shop::shop(player);
    std::println();
    printInventory(player);
    std::println("You escaped with {} gold remaining.", player.getGold());
    std::println();
    std::println("Thanks for shopping at Roscoe's potion emporium!");

    return 0;
}
