#include <print>
#include <format> // For specializing print to custom type
#include <iostream>
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
template <>
struct std::formatter<AdvertisingRevenue>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(const AdvertisingRevenue& ar, std::format_context& ctx)
    {
        const double revenue {ar.adsWatched
            * ar.adsClickedUserPercentage
            * ar.avgEarningPerAdClick};

        return std::format_to(
            ctx.out(), "{}", 5);

        // return std::format_to(
        //     ctx.out(),
        //     "Watched ads: {}"
        //     ", User click percentage: {}"
        //     ", Average earning per click: {}"
        //     "\nTotal revenue: {}",
        //     ar.adsWatched,
        //     ar.adsClickedUserPercentage,
        //     ar.avgEarningPerAdClick,
        //     revenue);
    }
};

struct Index {
    unsigned int id_{ 0 };
};

template <>
struct std::formatter<Index> {
    // for debugging only
    formatter() { std::cout << "formatter<Index>()\n"; }

    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Index& id, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "{}", id.id_);
    }
};


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

AdvertisingRevenue getAdvertisingReventue()
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
    // AdvertisingRevenue ar { getAdvertisingReventue() };
    // std::print("{}", ar);

    Index id{ 100 };
    std::print("id {}\n", id);
    std::print("id duplicated {0} {0}\n", id);


    return 0;
}