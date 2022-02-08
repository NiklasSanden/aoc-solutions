#include "solutions.hpp"

#include <istream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

constexpr std::string_view forward{ "forward" };
constexpr std::string_view up{ "up" };
constexpr std::string_view down{ "down" };

struct Input {
    std::string dir{};
    int amount{};
};
static std::istream& operator>>(std::istream& in, Input& input)
{
    in >> input.dir >> input.amount;
    if (input.dir == up)
        input.amount = -input.amount;
    return in;
}

std::string day2_2(std::istream& in)
{
    std::vector<Input> inputs{ std::istream_iterator<Input>{ in }, {} };
    auto forwards{
        inputs
        | std::views::filter([](const auto& i) { return i.dir == forward; })
        | std::views::transform([](const auto& i) { return i.amount; })
    };
    const auto horizontal{ std::reduce(forwards.begin(), forwards.end()) };

    const auto vertical{
        std::accumulate(inputs.begin(), inputs.end(), 0,
            [](const int a, const auto& b) {
                static int aim{ 0 };
                if (b.dir == forward)
                    return a + b.amount * aim;
                else {
                    aim += b.amount;
                    return a;
                }
            }
        )
    };

    return std::to_string(horizontal * vertical);
}
