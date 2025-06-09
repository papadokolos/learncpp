#pragma once

#include <string_view>
#include <print>
#include <iostream> // for cin

void ignoreLine();

// returns true if extraction failed, false otherwise
bool clearFailedExtraction();

// returns true if std::cin has unextracted input on the current line, false otherwise
bool hasUnextractedInput();

template <typename T>
[[deprecated("Old version, use newer below")]]
T getInputFromUser(std::string_view message)
{
    while (true)
    {
        std::print("{}", message);
        T value {};
        std::cin >> value;

        if (clearFailedExtraction())
        {
            continue;
        }
        if (hasUnextractedInput())
        {
            ignoreLine();
            continue;
        }
 
        return value;
    }
}


namespace Input
{
    // Options vs Flags:
    // https://unix.stackexchange.com/questions/285575/whats-the-difference-between-a-flag-an-option-and-an-argument#comment1183725_285588
    struct GetOptions
    {
        bool ignoreExtraneousInput { false };
    };

    template <typename T>
    T get(std::string_view message)
    {
        return get<T>(message, GetOptions{});
    }

    template <typename T>
    T get(std::string_view message, const GetOptions& options)
    {
        while (true)
        {
            std::print("{}", message);
            T value {};
            std::cin >> value;

            if (clearFailedExtraction())
            {
                continue;
            }
            if (hasUnextractedInput())
            {
                ignoreLine();
                if (!options.ignoreExtraneousInput)
                {
                    continue;
                }
            }
     
            return value;
        }
    }
}