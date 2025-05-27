#include <iostream>
#include <string>

// Run with address sanitizer.
// -----------------------------------------------------------------------------
// Returning by reference is okay here since the rvalue std::string("Hello") is
// destroyed after `s` is initialized (This is because rvalues are not destroyed
// until the end of the full expression in which they are created).
namespace NonDanglingReference
{

    const std::string& foo(const std::string& s)
    {
        return s;
    }

    std::string getHello()
    {
        return "Hello"; // implicit conversion to std::string
    }

    int main()
    {
        const std::string s{ foo(getHello()) };

        std::cout << s;

        return 0;
    }
}

// Returning by reference is bad here since the rvalue std::string("Hello")
// lifetime is not extended beyond the full expression in which it was created,
// making `s` a dangling reference right after its initialization. When `s` is
// initialized, the rvalue is alive, but it is destroyed afterwards. See:
// See:
// https://stackoverflow.com/questions/76026776/can-the-const-reference-of-function-return-formal-parameters-extend-the-lifetime
// Rvalue lifetime extension occurs when assigning a const-ref with a temporary
// value, and doesn't happen when assigning a const-ref with another const-ref.
namespace DanglingReference1
{

    const std::string& foo(const std::string& s)
    {
        return s;
    }

    std::string getHello()
    {
        return "Hello"; // implicit conversion to std::string
    }

    int main()
    {
        const std::string& s{ foo(getHello()) };

        std::cout << s;

        return 0;
    }
}

// This code triggers ASan stack-use-after-scope due to dangling reference `s`
namespace DanglingReference2
{
    std::string& foo(const std::string& s)
    {
        return const_cast<std::string&>(s);
    }

    std::string getHello()
    {
        return "Hello"; // implicit conversion to std::string
    }

    int main()
    {
        std::string& s{ foo(getHello()) };

        std::cout << s;

        return 0;
    }
}

int main()
{
    NonDanglingReference::main();
    DanglingReference1::main();
    DanglingReference2::main();

    return 0;
}