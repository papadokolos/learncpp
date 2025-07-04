#pragma once

class InvalidValue
{
public:
    template <typename T>
    operator T()
    {
        static_assert(false, "Cannot initialize with invalid value.");
    }
};
