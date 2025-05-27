#include <print>
#include <string_view>


enum class Animal
{
    pig,
    chicken,
    goat,
    cat,
    dog,
    duck,
};

constexpr std::string_view getAnimalName(Animal animal)
{
    using enum Animal;

    switch(animal)
    {
    case pig: return "pig";
    case chicken: return "chicken";
    case goat: return "goat";
    case cat: return "cat";
    case dog: return "dog";
    case duck: return "duck";
    default: return "???";
    }
}

constexpr int getAnimalLegsNumber(Animal animal)
{
    switch(animal)
    {
    using enum Animal;
    case pig: return 2;
    case chicken: return 2;
    case goat: return 4;
    case cat: return 4;
    case dog: return 4;
    case duck: return 2;
    default: return -1;
    }
}

void printNumberOfLegs(Animal animal)
{
    std::string_view animalName {getAnimalName(animal)};
    int animalLegs {getAnimalLegsNumber(animal)};
    std::println("A {} has {} legs.", animalName, animalLegs);
}

int main(int /*argc*/, char const */*argv*/[])
{
    printNumberOfLegs(Animal::cat);
    printNumberOfLegs(Animal::chicken);

    return 0;
}