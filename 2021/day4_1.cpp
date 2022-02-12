#include "solutions.h"

#include <algorithm>
#include <functional>
#include <istream>
#include <iterator>
#include <numeric>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

constexpr std::array<int, 0>::size_type board_size{ 5 };
struct Square {
    int value{};
    bool is_hit{ false };
};
struct Board {
    std::array<std::array<Square, board_size>, board_size> squares{};
    bool has_won{ false };
};
static std::istream& operator>>(std::istream& in, Board& board)
{
    for (auto& row : board.squares) {
        std::string s{};
        std::getline(in >> std::ws, s);
        std::istringstream ss{ s };

        std::ranges::for_each(row, [&ss](auto& square) { ss >> square.value; });
    }
    return in;
}

static std::optional<Board> draw_and_get_winner(std::vector<Board>& boards, const int draw){
    using namespace std::placeholders;
    const auto is_line_hit{
        std::bind(std::ranges::all_of, _1, [](const auto square) { return square.is_hit; })
    };

    for (auto& board : boards) {

        for (auto& row : board.squares) {
            std::ranges::transform(row, row.begin(),
                [draw](const auto square) -> Square {
                    return { square.value, square.is_hit || square.value == draw };
                }
            );
            if (is_line_hit(row)) {
                board.has_won = true;
            }
        }

        for (auto i{ 0ull }; i < board_size; ++i) {
            auto column{
                board.squares
                    | std::views::transform([i](const auto& row) -> Square { return row[i]; })
            };
            if (is_line_hit(column)) {
                board.has_won = true;
            }
        }
        if (board.has_won)
            return board;
    }

    return {};
}

static int calculate_winning_board_sum(const Board& board)
{
    return std::transform_reduce(board.squares.cbegin(), board.squares.cend(), 0, std::plus{},
        [](const auto& row) -> int {
            return std::transform_reduce(row.cbegin(), row.cend(), 0, std::plus{},
                [](const auto square) -> int {
                    return !square.is_hit * square.value;
                }
            );
        }
    );
}

std::string day4_1(std::istream& in)
{
    std::string random_numbers_line{};
    std::getline(in, random_numbers_line);
    auto random_numbers{
        random_numbers_line
            | std::views::split(',')
            | std::views::transform([](auto v){
                auto common_v{ v | std::views::common };
                return std::stoi(std::string{ common_v.begin(), common_v.end() });
            })
    };

    std::vector<Board> boards{ std::istream_iterator<Board>{ in }, {} };

    for (const auto draw : random_numbers) {
        const auto board{ draw_and_get_winner(boards, draw) };
        if (board) {
            return std::to_string(draw * calculate_winning_board_sum(*board));
        }
    }

    return "";
}
