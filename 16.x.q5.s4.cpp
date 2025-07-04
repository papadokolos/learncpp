#include "Random.h"
#include "CInTools.h"

#include <expected>
#include <cctype>
#include <cstddef>
#include <expected>
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

class InvalidValue
{
public:
    template <typename T>
    operator T()
    {
        static_assert(false, "Cannot initialize with an invalid value");
    }
};

class Session
{
public:
    enum GuessError
    {
        invalidGuessValue,
        duplicateGuess,
        tooManyGuesses,
    };

    const int maxWrongGuesses{ InvalidDefaultValue{} };

    Session(std::string_view word, int maxWrongGuesses);

    auto getWord() const { return m_word; }
    auto getWrongGuessesLeft() const { return m_wrongGuessesLeft; }

    /**
     * Guess a letter. Returns True for correct guess.
     * False for wrong guess. `GuessError` for invalid guess.
     */
    auto guess(char letter) -> std::expected<bool, GuessError>;
    bool wasGuessed(char letter) const;
    bool isCorrectGuess(char letter) const;

private:
    // Enforce explicit initialization of member variable
    using InvalidDefaultValue = InvalidValue;

    static constexpr int lettersInAlphabet{ 26 };

    std::size_t getGuessedLetterIndex(char letter) const;

    const std::string_view m_word{ InvalidDefaultValue{} };
    std::vector<bool> m_guessedLetters{ std::vector<bool>(lettersInAlphabet) };
    int m_wrongGuessesLeft{ InvalidDefaultValue{} };
};

Session::Session(std::string_view word, int maxWrongGuesses)
    : maxWrongGuesses{ maxWrongGuesses }
    , m_word{ word }
    , m_wrongGuessesLeft{ maxWrongGuesses }
{}

auto Session::guess(char letter)
    -> std::expected<bool, GuessError>
{
    std::expected<bool, GuessError> result{};

    if (m_wrongGuessesLeft <= 0)
    {
        result = std::unexpected(Session::tooManyGuesses);
    }
    else if (!std::islower(letter))
    {
        result = std::unexpected(Session::invalidGuessValue);
    }
    else if (m_guessedLetters[getGuessedLetterIndex(letter)])
    {
        result = std::unexpected(Session::duplicateGuess);
    }
    else
    {
        if (!isCorrectGuess(letter))
        {
            --m_wrongGuessesLeft;
        }

        result = isCorrectGuess(letter);
        m_guessedLetters[getGuessedLetterIndex(letter)] = true;
    }

    return result;
}

bool Session::wasGuessed(char letter) const
{
    return m_guessedLetters[getGuessedLetterIndex(letter)];
}

bool Session::isCorrectGuess(char guessedLetter) const
{
    for (char correctLetter : getWord())
    {
        if (guessedLetter == correctLetter)
        {
            return true;
        }
    }

    return false;
}

std::size_t Session::getGuessedLetterIndex(char letter) const
{
    // Assuming integer representations of alphabet letters are consecutive. 
    return static_cast<std::size_t>(letter % 'a');
}


std::string buildWrongGuessesAsString(const Session& session)
{
    constexpr std::string_view alphabet{ "abcdefghijklmnopqrstuvwxyz" };

    std::string wrongLetters{};
    for (char letter : alphabet)
    {
        if (session.wasGuessed(letter) && !session.isCorrectGuess(letter))
        {
            wrongLetters += letter;
        }
    }

    return wrongLetters;
}

std::string buildCensoredWord(const Session& session)
{
    std::string censoredWord{ session.getWord() };
    for (char& letter : censoredWord)
    {
        if (!session.wasGuessed(letter))
        {
            letter = '_';
        }
    }

    return censoredWord;
}

void printState(const Session& session)
{
    std::string wrongLetters{ buildWrongGuessesAsString(session) };
    std::string censoredWord{ buildCensoredWord(session) };

    std::println(
        "The word: {}   Wrong guesses: {:+>{}}",
        censoredWord,
        wrongLetters,
        session.maxWrongGuesses);
}

void performGuess(Session& session)
{
    while (true)
    {
        const char letter{ Input::get<char>("Enter your next letter: ") };
        if (const auto result{ session.guess(letter) }; result)
        {
            const bool correctGuess{ result.value() };
            if (!correctGuess)
            {
                std::println("Incorrect guess.");
            }
            else
            {
                std::println("Correct guess.");
            }

            return;
        }
        else
        {
            switch (result.error())
            {
            case Session::GuessError::invalidGuessValue:
                std::println("That wasn't a valid input.  Try again.");
                break;
            case Session::GuessError::duplicateGuess:
                std::println("You already guessed that.  Try again.");
                break;
            case Session::GuessError::tooManyGuesses:
                std::println("Max tries exceeded. Game should have been over.");
                break;
            }
        }
    }
}

bool isGameLost(const Session& session)
{
    return session.getWrongGuessesLeft() <= 0;
}

bool isGameWon(const Session& session)
{
    for (char letter : session.getWord())
    {
        if (!session.wasGuessed(letter))
        {
            return false;
        }
    }

    return true;
}

int main(int /*argc*/, char const */*argv*/[])
{
    std::puts("Welcome to C++man (a variant of Hangman)");
    std::puts("To win: guess the word.  To lose: run out of pluses.\n");

    constexpr int tries{ 6 };
    Session session{ WordList::pickRandomWord(), tries };
    printState(session);

    while (true)
    {
        performGuess(session);
        std::println();
        printState(session);

        if (isGameLost(session))
        {
            std::println("You lost! The word was: {}", session.getWord());
            break;
        }
        if (isGameWon(session))
        {
            std::println(
                "You Won! Congrats :)",
                session.getWrongGuessesLeft());
            break;
        }
    }


    return 0;
}