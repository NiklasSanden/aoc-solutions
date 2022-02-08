#include "solutions.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <istream>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

static int get_value(
    std::vector<std::string_view> copied_values,
    const std::function<char(int, int)>& comp)
{
    for (std::size_t i{ 0 }; i < copied_values.front().size() && copied_values.size() > 1; ++i) {
        const auto ones{
            std::ranges::count_if(
                copied_values | std::views::transform([i](const auto& s) { return s[i]; }),
                [](const char c) { return c == '1'; }
            )
        };
        const auto c{ comp(ones, static_cast<int>((copied_values.size() + 1) / 2)) ? '1' : '0' };
        const auto [first, last]{
            std::ranges::remove_if(copied_values, [i, c](const auto& s) { return s[i] != c; })
        };
        copied_values.erase(first, last);
    }
    return std::stoi(std::string{ copied_values.front() }, nullptr, 2);
}

std::string day3_2(std::istream& in)
{
    const std::vector<std::string> values{ std::istream_iterator<std::string>{ in }, {} };
    const std::vector<std::string_view> view_of_values{ values.cbegin(), values.cend() };
    return std::to_string(
        get_value(view_of_values, std::greater_equal{}) * get_value(view_of_values, std::less{})
    );
}
