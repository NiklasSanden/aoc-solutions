#include "solutions.hpp"

#include <algorithm>
#include <functional>
#include <istream>
#include <iterator>
#include <string>

constexpr int window_size{ 3 };
std::string day1_2(std::istream& in)
{
    std::vector<int> values{ std::istream_iterator<int>{ in }, {} };

    int value{ 0 };
    if (values.size() > static_cast<decltype(values)::size_type>(window_size)) {
        std::vector differences(values.size() - window_size + 1, 0);
        std::transform(values.cbegin() + window_size, values.cend(),
            values.cbegin(), differences.begin() + 1, std::minus{}
        );
        value = std::ranges::count_if(differences, std::bind_front(std::less{}, 0));
    }
    return std::to_string(value);
}
