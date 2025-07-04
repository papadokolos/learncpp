#include "CInTools.h"
#include "Random.h"

#include <cmath>
#include <print>
#include <vector>
#include <ranges>


class InvalidValue
{
public:
    template <typename T>
    operator T()
    {
        static_assert(false, "Cannot initialize with invalid value.");
    }
};

class SessionData
{
public:
    using Numbers = std::vector<int>;

    SessionData(int startNum, int numNums, int multiplier);

    const int startNum{ InvalidValue{} };
    const int numNums{ InvalidValue{} };
    const int multiplier{ InvalidValue{} };
    Numbers nums{ InvalidValue{} };

private:
    static constexpr Numbers createNums(
        int startNum, int numNums, int multiplier);
};

SessionData::SessionData(int startNum, int numNums, int multiplier)
    : startNum{ startNum }
    , numNums{ numNums }
    , multiplier{ multiplier }
    , nums{ createNums(startNum, numNums, multiplier) }
{}

constexpr SessionData::Numbers SessionData::createNums(
    int startNum, int numNums, int multiplier)
{
    constexpr auto makeSquared{
        [](int num) { return num * num; }
    };
    const auto multiplyWithMultiplier{
        [multiplier](int num) { return num * multiplier; }
    };

    return std::views::iota(startNum)
        | std::views::take(numNums)
        | std::views::transform(makeSquared)
        | std::views::transform(multiplyWithMultiplier)
        | std::ranges::to<std::vector>();
}

SessionData setup()
{
    constexpr int minMultiplier{ 2 };
    constexpr int maxMultiplier{ 4 };

    const int startNum{ Input::get<int>("Start where? ") };
    const int numNums{ Input::get<int>("How many? ") };
    const int multiplier{ Random::get(minMultiplier, maxMultiplier) };

    return SessionData{ startNum, numNums, multiplier };
}

template <typename T>
int findClosest(const std::vector<T>& arr, const T& value)
{
    const auto closerToValue{
        [value](int closestValue, int newValue)
        {
            auto minDistance{ std::abs(value - closestValue) };
            auto newDistance{ std::abs(value - newValue) };

            return minDistance < newDistance;
        }
    };

    return *std::ranges::min_element(arr, closerToValue);
}

enum class State
{
    inProgress,
    lost,
    won,
};

State handleGuess(int guess, SessionData& data)
{
    const auto result{ std::ranges::find(data.nums, guess) };
    if (result == data.nums.end())
    {
        std::println(
        "{} is wrong! Try {} next time.", guess, findClosest(data.nums, guess));

        return State::lost;
    }
    else
    {
        data.nums.erase(result);

        if (data.nums.empty())
        {
            std::println("Nice! You found all numbers, good job!");
            return State::won;
        }
        else
        {
            std::println("Nice! {} number(s) left.", data.nums.size());
            return State::inProgress;
        }
    }
}

void run(SessionData& data)
{
    std::println(
        "I generated {} square numbers."
        " Do you know what each number is after multiplying it by {}?",
        data.numNums,
        data.multiplier);

    while (true)
    {
        const int guess{ Input::get<int>("") };
        const auto gameState{ handleGuess(guess, data) };
        const bool isGameOver{ gameState != State::inProgress };
        if (isGameOver)
        {
            return;
        }
    }
}

int main(int /*argc*/, char const */*argv*/[])
{
    SessionData data{ setup() };
    run(data);

    return 0;
}
