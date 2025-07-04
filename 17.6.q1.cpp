#include "CInTools.h"

#include <array>
#include <iterator>
#include <optional>
#include <print>
#include <ranges>
#include <source_location>
#include <string>


namespace Animal
{
    constexpr int beforeEnum{ std::source_location::current().line() };
    enum Type
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
    };
    constexpr int afterEnum{ std::source_location::current().line() };
    constexpr int extraLines{ 4 };
    constexpr int numTypes{ afterEnum - beforeEnum - extraLines };

    struct Data
    {
        std::string name{};
        int numLegs{};
        std::string sound{};
    };

    constexpr std::array dataPerType{
        Data{"chicken",  2, "coocooricoo"}, 
        Data{"dog",      4, "hav"}, 
        Data{"cat",      4, "meouw"}, 
        Data{"elephant", 4, "hieeeeeeeeeeeuooooooo"}, 
        Data{"duck",     2, "quack"}, 
        Data{"snake",    0, "psssst"},
    };
    static_assert(std::size(dataPerType) == numTypes);

    std::optional<Animal::Type> fromString(std::string_view animal)
    {
        if      (animal == "chicken")  { return Animal::chicken; }
        else if (animal == "dog")      { return Animal::dog; }
        else if (animal == "cat")      { return Animal::cat; }
        else if (animal == "elephant") { return Animal::elephant; }
        else if (animal == "duck")     { return Animal::duck; }
        else if (animal == "snake")    { return Animal::snake; }
        else { return std::nullopt; }
    }

    void print(Animal::Type animalType)
    {
        const Animal::Data& animalData{ Animal::dataPerType[animalType] };
        std::println(
            "A {} has {} legs and says {}.",
            animalData.name,
            animalData.numLegs,
            animalData.sound
        );
    }
}

namespace 
{
    void _printRestOfAnimals(std::optional<Animal::Type> excludeAnimal)
    {
        std::println("Here is the data for the rest of the animals:");
        for (int index
            : std::views::iota(0, std::ssize(Animal::dataPerType))
            | std::views::filter(
                [excludeAnimal](int i)
                {
                    return excludeAnimal ? i != *excludeAnimal : true;
                })
            )
        {
            print(static_cast<Animal::Type>(index));
        }
    }
}

void printRestOfAnimals()
{
    _printRestOfAnimals(std::nullopt);
}

void printRestOfAnimals(Animal::Type excludeAnimal)
{
    _printRestOfAnimals(excludeAnimal);
}


int main(int /*argc*/, char const */*argv*/[])
{
    std::string animalAsString{
        Input::get<std::string>("Enter an animal: ")
    };
    
    // Version 1
    if (auto result{ Animal::fromString(animalAsString) }; result)
    {
        print(*result);
        std::println();
        printRestOfAnimals(*result);
    }
    else
    {
        std::println("That animal couldn't be found.", animalAsString);
        std::println();
        printRestOfAnimals();
    }

    // Version 2
    Animal::fromString(animalAsString).and_then(
        [](Animal::Type animal)
    {
        print(animal);
        std::println();
        printRestOfAnimals(animal);

        return std::make_optional(animal);
    }).or_else(
        []()
    {
        std::println("That animal couldn't be found.");
        std::println();
        printRestOfAnimals();

        return std::optional<Animal::Type>{};
    });


    return 0;
}