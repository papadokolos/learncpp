#include <print>
#include <string>


struct Monster
{
    enum class Type
    {
        ogre,
        dragon,
        orc,
        giantSpider,
        slime,
    };

    Type type;
    std::string name {};
    int health {};
};

constexpr std::string_view convertMonsterTypeToString(
    Monster::Type monster_type)
{
    switch (monster_type)
    {
    using enum Monster::Type;
    case ogre:        return "Ogre";
    case dragon:      return "Dragon";
    case orc:         return "Orc";
    case giantSpider: return "Giant Spider";
    case slime:       return "Slime";
    default:          return "???";
    }
}

void printMonster(const Monster& monster)
{
    std::string_view monsterType { convertMonsterTypeToString(monster.type) };

    std::println(
        "This {} is named {} and has {} health.",
        monsterType, monster.name, monster.health);
}


int main(int /*argc*/, char const */*argv*/[])
{
    Monster ogre {
        .type { Monster::Type::ogre },
        .name { "Torg" },
        .health { 145 },
    };

    Monster slime {
        .type { Monster::Type::slime },
        .name { "Blurp" },
        .health { 23 },
    };

    printMonster(ogre);
    printMonster(slime);


    return 0;
}