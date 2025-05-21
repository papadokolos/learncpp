#include <iostream>
#include <print>

// https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/
#include "Random.h"
#include "CInTools.h"


namespace Constants
{
    constexpr int minNumber{ 1 };
    constexpr int maxNumber{ 100 };
    constexpr int maxGuesses{ 7 };
}

int getGuess(int guessNum, int minNumber, int maxNumber)
{
    while (true)
    {
        std::print("Guess #{}: ", guessNum);
        int guess{};
        std::cin >> guess;

        if (clearFailedExtraction())
        {
            std::println("Your guess is invalid.", guess);
        }
        else if (hasUnextractedInput())
        {
            ignoreLine();
            std::println("Your guess is invalid.", guess);
        }
        else if (guess < minNumber || guess > maxNumber)
        {
            std::println("Your guess ({}) is out of bounds: [{}, {}]",
               guess, minNumber, maxNumber);
        }
        else
        {
            return guess;
        }
    }
}

void gameLost(int number)
{
    std::println("Sorry, you lose. The correct number was {}.", number);
}

/**
 * Check whether guess is correct, and inform the user.
 *
 * @return     Whether the guess is correct
 */
bool respondToGuess(int number, int guess)
{
    if (guess > number)
    {
        std::puts("Your guess is too high.");
    }
    else if (guess < number)
    {
        std::puts("Your guess is too low.");
    }
    else
    {
        std::puts("Correct! You win!");
        return true;
    }

    return false;
}

void runHiLoGame(int maxGuesses, int minNumber, int maxNumber)
{
    std::println(
        "Let's play a game. I'm thinking of a number between {} and {}."
        " You have 7 tries to guess what it is.",
        minNumber,
        maxNumber);

    const int number{ Random::get(Constants::minNumber, Constants::maxNumber) };

    for (int guessNum{ 1 }; guessNum <= maxGuesses; ++guessNum)
    {
        const int guess{ getGuess(guessNum, minNumber, maxNumber) };
        if (respondToGuess(number, guess))
        {
            return;
        }
    }

    gameLost(number);
}

bool askForReplay()
{
    while (true)
    {
        std::print("Would you like to play again (y/n)? ");
        char answer{};
        std::cin >> answer;

        if (clearFailedExtraction())
        {
            continue;
        }
        else if (hasUnextractedInput())
        {
            ignoreLine();
            continue;
        }

        switch (answer)
        {
        case 'y':
            return true;
        case 'n':
            std::puts("Thank you for playing.");
            return false;
        }
    }
}

int main(int /*argc*/, char const */*argv*/[])
{
    while (true)
    {
        runHiLoGame(
            Constants::maxGuesses,
            Constants::minNumber,
            Constants::maxNumber);

        if (!askForReplay())
        {
            break;
        }
    }


    return 0;
}