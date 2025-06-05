#include "Random.h"

#include <print>
#include <string>
#include <string_view>


class Monster
{
public:
    enum Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        maxMonsterTypes,
    };

    Monster(
        Type type,
        std::string_view name,
        std::string_view roar,
        int numHitPoints)
        : m_type { type }
        , m_name { name }
        , m_roar { roar }
        , m_numHitPoints { numHitPoints }
    {}

    std::string_view getTypeString() const;
    void print() const;

private:
    Type m_type {};
    std::string m_name {};
    std::string m_roar {};
    int m_numHitPoints {};
};

std::string_view Monster::getTypeString() const
{
    switch (m_type)
    {
    case dragon:   return "Dragon";
    case goblin:   return "Goblin";
    case ogre:     return "Ogre";
    case orc:      return "Orc";
    case skeleton: return "Skeleton";
    case troll:    return "Troll";
    case vampire:  return "Vampire";
    case zombie:   return "Zombie";
    default:       return "???";
    }
}

void Monster::print() const
{
    if (m_numHitPoints > 0)
    {
        std::println("{} the {} has {} hit points and says {}.",
            m_name, getTypeString(), m_numHitPoints, m_roar);
    }
    else
    {
        std::println("{} the {} is dead.", m_name, getTypeString());
    }
}


namespace MonsterGenerator
{
    std::string_view getName(int number)
    {
        switch (number)
        {
        case 0:  return "Blarg";
        case 1:  return "Moog";
        case 2:  return "Pksh";
        case 3:  return "Tyrn";
        case 4:  return "Mort";
        case 5:  return "Hans";
        default: return "???";
        }
    }

    std::string_view getRoar(int number)
    {
        switch (number)
        {
        case 0:  return "*ROAR*";
        case 1:  return "*peep*";
        case 2:  return "*squeal*";
        case 3:  return "*whine*";
        case 4:  return "*growl*";
        case 5:  return "*burp*";
        default: return "???";
        }
    }

    Monster generate()
    {
        using Monster::maxMonsterTypes;
        constexpr int maxNames { 5 };
        constexpr int maxRoars { 5 };
        constexpr int minHitPoints { 1 };
        constexpr int maxHitPoints { 100 };

        const Monster::Type type {
            static_cast<Monster::Type>(
                Random::get(0, maxMonsterTypes - 1) // Excluding maxMonsterTypes
            )
        };
        const std::string_view name { getName(Random::get(0, maxNames)) };
        const std::string_view roar { getRoar(Random::get(0, maxRoars)) };
        const int numHitPoints { Random::get(minHitPoints, maxHitPoints) };

        return Monster{ type, name, roar, numHitPoints };
    }
}


int main()
{
    Monster m{ MonsterGenerator::generate() };
    m.print();

    return 0;
}