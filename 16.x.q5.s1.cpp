#include "Random.h"

#include <cstddef>
#include <print>
#include <string_view>


namespace WordList
{
    const std::vector<std::string_view> words{
        "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion",
        "beautiful", "distance", "luggage" };

    std::string_view getRandomWord()
    {
        return words[Random::get(0uz, words.size() - 1)];
    }
}

int main(int /*argc*/, char const */*argv*/[])
{
    std::puts("Welcome to C++man (a variant of Hangman)");
    std::puts("To win: guess the word.  To lose: run out of pluses.\n");

    std::println("The word is: {}", WordList::getRandomWord());

    return 0;
}