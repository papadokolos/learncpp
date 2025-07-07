#include <print>
#include <format> // For specializing print to custom type
#include <string_view>

#include "CInTools.h"


struct AdvertisingRevenue
{
    int adsWatched {};
    double adsClickedUserPercentage {};
    double avgEarningPerAdClick {};
};

// std::formatter specialization for my custom type
// (instead of overloading operator<< of std::cout)
// Based on:
// - https://stackoverflow.com/questions/79096443/what-is-the-correct-way-to-implement-a-custom-stdformatter-in-c20
// - https://stackoverflow.com/questions/75543234/how-to-forward-formatting-information-from-stdformat
// - https://stackoverflow.com/questions/59909102/stdformat-of-user-defined-types
template <>
struct std::formatter<AdvertisingRevenue>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template<typename ParseContext>
    auto format(const AdvertisingRevenue& ar, ParseContext& ctx) const
    {
        constexpr std::string_view format {
            "Watched ads: {}"
            "\nUser click percentage: {}%"
            "\nAverage earning per click: {}"
            "\n-------------------------------"
            "\nTotal revenue: {}"
        };

        const double revenue {
            ar.adsWatched
            * (ar.adsClickedUserPercentage / 100) // percent to fraction
            * ar.avgEarningPerAdClick };

        ctx.advance_to(
            std::format_to(
                ctx.out(),
                format,
                ar.adsWatched,
                ar.adsClickedUserPercentage,
                ar.avgEarningPerAdClick,
                revenue));

        return ctx.out();
    }
};

AdvertisingRevenue getAdvertisingRevenue()
{
    constexpr std::string_view adsWatchedMessage {
        "How many ads were watched: "
    };
    constexpr std::string_view adsClickedMessage {
        "What is the user click percentage: "
    };
    constexpr std::string_view avgEearningMessage {
        "What is the average earning per ad click: "
    };

    return {
        .adsWatched = getInputFromUser<int>(adsWatchedMessage),
        .adsClickedUserPercentage = getInputFromUser<double>(adsClickedMessage),
        .avgEarningPerAdClick = getInputFromUser<double>(avgEearningMessage)
    };
}


int main(int /*argc*/, char const */*argv*/[])
{
    AdvertisingRevenue ar { getAdvertisingRevenue() };
    std::println("Your advertising revenue:\n{}", ar);

    return 0;
}