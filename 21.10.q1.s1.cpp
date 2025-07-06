#include <cstddef>
#include <print>
#include <string>
#include <string_view>

class MyString
{
public:
    MyString() = default;
    MyString(std::string_view string) : m_string{ string } {}

    /**
     * Slice MyString starting from `startIndex` up to `numLetters` or end of
     * string (in case `numLetters` is too big).
     */
    MyString operator()(std::size_t startIndex, std::size_t numLetters) const;
private:
    friend std::formatter<MyString>;

    std::string m_string{};
};

MyString MyString::operator()(
    std::size_t startIndex, std::size_t numLetters) const
{
    return MyString{ m_string.substr(startIndex, numLetters) };
}

template <>
struct std::formatter<MyString>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename ParseContext>
    auto format(MyString string, ParseContext& ctx) const
    {
        ctx.advance_to(
            std::format_to(
                ctx.out(), "{}", string.m_string
            )
        );

        return ctx.out();
    }
};

int main()
{
    MyString s { "Hello, world!" };
    std::println("{}", s(7, 5)); // start at index 7 and return 5 characters

    return 0;
}
