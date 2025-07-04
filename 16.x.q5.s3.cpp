#include "Random.h"
#include "CInTools.h"

#include <cctype>
#include <cstddef>
#include <print>
#include <string_view>
#include <vector>


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
    Session(std::string_view word) : m_word{ word }
    {}

    auto getWord() const { return m_word; }
    
    void addGuess(char guessedLetter);
    bool isGuessedLetter(char letter) const;

private:
    static constexpr int lettersInAlphabet{ 26 };

    std::size_t getGuessedLetterIndex(char letter) const;

    const std::string_view m_word{};
    std::vector<bool> m_guessedLetters{ std::vector<bool>(lettersInAlphabet) };
};

void Session::addGuess(char guessedLetter)
{
    m_guessedLetters[getGuessedLetterIndex(guessedLetter)] = true;
}

bool Session::isGuessedLetter(char letter) const
{
    return m_guessedLetters[getGuessedLetterIndex(letter)];
}

std::size_t Session::getGuessedLetterIndex(char letter) const
{
    // Assuming integer representations of alphabet letters are consecutive. 
    return static_cast<std::size_t>(letter % 'a');
}


void printState(const Session& session)
{
    std::string censoredWord{ session.getWord() };
    for (char& letter : censoredWord)
    {
        if (!session.isGuessedLetter(letter))
        {
            letter = '_';
        }
    }

    std::println("The word: {}", censoredWord);
}

char getGuessLetterFromCLI(const Session& session)
{
    while (true)
    {
        char letter{ Input::get<char>("Enter your next letter: ") };
        if (std::islower(letter))
        {
            if (!session.isGuessedLetter(letter))
            {
                return letter;
            }
            
            std::println("You already guessed that.  Try again.");
        }
        else
        {
            std::println("That wasn't a valid input.  Try again.");
        }
    }
}

int main(int /*argc*/, char const */*argv*/[])
{
    std::puts("Welcome to C++man (a variant of Hangman)");
    std::puts("To win: guess the word.  To lose: run out of pluses.\n");

    Session session{ WordList::pickRandomWord() };
    printState(session);

    constexpr int tries{ 6 };
    for (int counter{ 0 }; counter < tries; ++counter)
    {
        char letter{ getGuessLetterFromCLI(session) };
        session.addGuess(letter);
        std::println();
        printState(session);
    }

    return 0;
}