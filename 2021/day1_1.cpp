#include "solutions.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <istream>
#include <iterator>
#include <numeric>
#include <string>

std::string day1_1(std::istream& in)
{
    std::vector<int> values{ std::istream_iterator<int>{ in }, {} };
    assert(!values.empty() && "Input read was empty");

    std::adjacent_difference(values.cbegin(), values.cend(), values.begin());
    return std::to_string(
        std::count_if(values.cbegin() + 1, values.cend(), std::bind_front(std::less{}, 0))
    );
}
