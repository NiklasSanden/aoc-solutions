#include "solutions.hpp"

#include <algorithm>
#include <cstddef>
#include <istream>
#include <iterator>
#include <ranges>
#include <string>
#include <vector>

std::string day3_1(std::istream& in)
{
    const std::vector<std::string> values{ std::istream_iterator<std::string>{ in }, {} };

    std::string gamma{ values.front() };
    std::string epsilon{ values.front() };
    for (std::size_t i{ 0 }; i < gamma.size(); ++i) {
        const auto ones{
            std::ranges::count_if(
                values | std::views::transform([i](const auto& s) { return s[i]; }),
                [](const char c) { return c == '1'; }
            )
        };
        const auto is_one_majority{ ones > static_cast<int>(values.size() / 2) };
        gamma[i] = is_one_majority ? '1' : '0';
        epsilon[i] = is_one_majority ? '0' : '1';
    }

    return std::to_string(
        std::stoi(gamma, nullptr, 2) * std::stoi(epsilon, nullptr, 2)
    );
}
