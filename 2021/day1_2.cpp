#include "solutions.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <istream>
#include <iterator>
#include <string>

constexpr int window_size{ 3 };
std::string day1_2(std::istream& in)
{
    const std::vector<int> values{ std::istream_iterator<int>{ in }, {} };
    assert(values.size() > static_cast<decltype(values)::size_type>(window_size)
           && "Input read was empty or otherwise trivial");

    std::vector differences(values.size() - window_size + 1, 0);
    std::transform(values.cbegin() + window_size, values.cend(),
        values.cbegin(), differences.begin() + 1, std::minus{}
    );
    return std::to_string(
        std::ranges::count_if(differences, std::bind_front(std::less{}, 0))
    );
}
