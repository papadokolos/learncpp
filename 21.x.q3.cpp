#include "InvalidValue.h"

#include <algorithm>
#include <cassert>
#include <format>
#include <print>
#include <span>
#include <utility>


class IntArray
{
public:
    IntArray() = delete;

    /**
     * Create array with positive length.
     */
    explicit IntArray(int length);

    // Rule of 5
    IntArray(const IntArray& other);
    IntArray(IntArray&& other);
    ~IntArray();
    IntArray& operator=(IntArray other);
    IntArray& operator=(IntArray&& other);

    // https://stackoverflow.com/a/69486322
    auto&& operator[](this auto&& self, int index);

    int length() const { return m_length; }

    // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    friend void swap(IntArray& lhs, IntArray& rhs);

    friend struct std::formatter<IntArray>;

private:
    static std::size_t toAllocationSize(int length);

    int* m_arr{ InvalidValue{} }; // smart pointers not yet introduced
    int m_length{ InvalidValue{} };
};

void swap(IntArray& lhs, IntArray& rhs)
{
    using std::swap;

    swap(lhs.m_arr, rhs.m_arr);
    swap(lhs.m_length, rhs.m_length);
}

std::size_t IntArray::toAllocationSize(int length)
{
    assert(length > 0);
    return static_cast<std::size_t>(length);
}

IntArray::IntArray(int length)
    : m_arr{ new int[toAllocationSize(length)]{} }
    , m_length{ length }
{}

IntArray::IntArray(const IntArray& other) : IntArray(other.length())
{
    std::ranges::copy_n(other.m_arr, other.m_length, m_arr);
}

IntArray::IntArray(IntArray&& other) : m_arr{ nullptr }, m_length{ 0 }
{
    swap(*this, other);
}

IntArray::~IntArray()
{
    delete[] m_arr;
}

IntArray& IntArray::operator=(IntArray other)
{
    swap(*this, other);

    return *this;
}

IntArray& IntArray::operator=(IntArray&& other)
{
    swap(*this, other);

    return *this;
}

auto&& IntArray::operator[](this auto&& self, int index)
{
    bool indexInBounds{ (index >= 0) && (index < self.m_length) };
    assert(indexInBounds);

    return std::forward<decltype(self)>(self).m_arr[index];
}

template <>
struct std::formatter<IntArray>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(const IntArray& arr, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(),
                "{}",
                std::span(arr.m_arr, static_cast<std::size_t>(arr.m_length))
            )
        );

        return ctx.out();
    }
};

IntArray fillArray()
{
    IntArray a(5);

    a[0] = 5;
    a[1] = 8;
    a[2] = 2;
    a[3] = 3;
    a[4] = 6;

    return a;
}


int main()
{
    IntArray a{ fillArray() };

    std::println("{}", a);

    auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
    a = ref;

    IntArray b(1);
    b = a;

    a[4] = 7;

    std::println("{}", b);

    return 0;
}
