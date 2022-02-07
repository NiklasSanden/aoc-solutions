#include "solutions.hpp"

#include <algorithm>
#include <functional>
#include <istream>
#include <iterator>
#include <numeric>
#include <string>

std::string day1_1(std::istream& in)
{
    using namespace std::placeholders;
    std::vector<int> values{ std::istream_iterator<int>{ in }, {} };
    if (values.empty())
        return "0";

    std::adjacent_difference(values.cbegin(), values.cend(), values.begin());
    return std::to_string(
        std::count_if(values.cbegin() + 1, values.cend(), std::bind(std::greater{}, _1, 0))
    );
}
