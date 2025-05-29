#include <cstddef>
#include <print>
#include <ranges>


inline namespace V1
{
    // Manual loops, C++23 prints
    void printNumbersDownTo1(int max_number);
}
namespace V2
{
    // Manual padding, C++23 prints
    void printNumbersDownTo1(int max_number);
}
namespace V3
{
    // Automatic padding with C++23 prints, and fancy range-for
    void printNumbersDownTo1(int max_number);
}

int main()
{
    constexpr int max { 5 };

    printNumbersDownTo1(max);
    V2::printNumbersDownTo1(max);
    V3::printNumbersDownTo1(max);

    return 0;
}


inline namespace V1
{
    void printNumbersDownTo1(int max)
    {
        int outer{ 1 };
        while (outer <= max)
        {
            int inner{ max };
            while (inner > outer)
            {
                std::print("  ");
                --inner;
            }
            while (inner >= 2) // 1 is printed separately without a space
            {
                std::print("{} ", inner);
                --inner;
            }

            std::println("1");
            ++outer;
        }
    }
}
namespace V2
{
    void printPadding(int pad_size)
    {
        std::string padding(static_cast<std::size_t>(pad_size), ' ');
        std::print("{}", padding);
    }

    void printActualNumbers(int max)
    {
        int current_number{ max };
        while (current_number >= 2)
        {
            std::print("{} ", current_number);
            --current_number;
        }
        std::print("1"); // Printed separately to avoid extraneous space
    }

    void printNumbersDownTo1(int max)
    {
        int outer{ 1 };
        while (outer <= max)
        {
            printPadding((max - outer) * 2);
            printActualNumbers(outer);
            std::println();
            ++outer;
        }
    }
}
namespace V3
{
    void printNumbersDownTo1(int max)
    {
        int outer{ 1 };
        while (outer <= max)
        {
            // Since clang doesn't implement `std::views::join_with` yet,
            // I resort to ugly solution (which prints each number separately)

            // Print first number with appropriate padding
            const int pad_size{ (max - outer) * 2 + 1 };
            const int first_number { outer };
            std::print("{:>{}}", first_number, pad_size);

            // Print remaining numbers
            for (auto num
                : std::views::iota(1, first_number) | std::views::reverse)
            {
                std::print(" {}", num);
            }

            std::println();
            ++outer;
        }
    }
}