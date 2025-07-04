#include "Random.h"
#include "CInTools.h"

#include <cctype>
#include <cstddef>
#include <print>
#include <string_view>


namespace WordList
{
    const std::vector<std::string_view> words{
        "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion",
        "beautiful", "distance", "luggage" };

    std::string_view pickRandomWord()
    {
        return words[Random::get(0uz, words.size() - 1)];
    }
}

class Session
{
public:
    Session(std::string_view word) : m_word { word }
    {}

    std::string_view getWord() const { return m_word; }

private:
    const std::string_view m_word{};
};

void printState(const Session& session)
{
    std::string underscores(session.getWord().length(), '_');
    std::println("The word: {}", underscores);
}

char getLetterFromCLI()
{
    while (true)
    {
        char letter{ Input::get<char>("Enter your next letter: ") };
        if (std::islower(letter))
        {
            return letter;
        }

        std::println("That wasn't a valid input.  Try again.");
    }
}

int main(int /*argc*/, char const */*argv*/[])
{
    std::puts("Welcome to C++man (a variant of Hangman)");
    std::puts("To win: guess the word.  To lose: run out of pluses.\n");

    Session session{ WordList::pickRandomWord() };
    printState(session);
    std::println("You entered: {}", getLetterFromCLI());

    return 0;
}