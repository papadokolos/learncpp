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