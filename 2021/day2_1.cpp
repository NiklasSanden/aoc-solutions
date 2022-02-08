#include "solutions.hpp"

#include <algorithm>
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

std::string day2_1(std::istream& in)
{
    std::vector<Input> inputs{ std::istream_iterator<Input>{ in }, {} };
    const auto partition_distance{
        std::distance(
            inputs.begin(),
            std::ranges::partition(inputs, [](const auto& i) { return i.dir == forward; }).begin()
        )
    };
    auto amounts{ inputs | std::views::transform([](const auto& i) { return i.amount; }) };
    const auto partition_it{ amounts.begin() + partition_distance };
    const auto horizontal{ std::reduce(amounts.begin(), partition_it) };
    const auto vertical{ std::reduce(partition_it, amounts.end()) };

    return std::to_string(horizontal * vertical);
}
