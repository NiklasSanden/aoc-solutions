#include "solutions.h"

#include <array>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <ratio>
#include <stdexcept>
#include <string>

static const std::string input_path{ "input/2021/" };
static const std::string output_path{ "input/2021/" };

struct SolutionInfo {
    std::function<std::string(std::istream&)> solution{};
    std::string problem{};
    std::string input_file{};
    std::string output_file{};
};

static const std::array solutions{
    SolutionInfo{ day1_1, "Day 01 Part 1", "1_in", "1_1_out" },
    SolutionInfo{ day1_2, "Day 01 Part 2", "1_in", "1_2_out" },
    SolutionInfo{ day2_1, "Day 02 Part 1", "2_in", "2_1_out" },
    SolutionInfo{ day2_2, "Day 02 Part 2", "2_in", "2_2_out" },
    SolutionInfo{ day3_1, "Day 03 Part 1", "3_in", "3_1_out" },
    SolutionInfo{ day3_2, "Day 03 Part 2", "3_in", "3_2_out" },
    SolutionInfo{ day4_1, "Day 04 Part 1", "4_in", "4_1_out" },
    SolutionInfo{ day4_2, "Day 04 Part 2", "4_in", "4_2_out" }
};

int main()
{
    auto total_time{ 0.0 };
    auto num_correct{ 0 };
    for (const auto& info : solutions) {
        const auto input_file_path{ input_path + info.input_file };
        std::ifstream input{ input_file_path };
        if (!input)
            throw std::runtime_error("File not found exception: " + input_file_path);

        const auto start{ std::chrono::steady_clock::now() };
        const auto output{ info.solution(input) };
        const auto end{ std::chrono::steady_clock::now() };
        const auto execution_time{
            std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
                end - start
            ).count()
        };

        const auto output_file_path{ output_path + info.output_file };
        std::ifstream expected_output_file{ output_file_path };
        if (!expected_output_file)
            throw std::runtime_error("File not found exception: " + output_file_path);
        const std::string expected_output(
            std::istream_iterator<char>{ expected_output_file }, {}
        );

        const auto is_correct{ output == expected_output };
        std::cout
            << info.problem << '\n'
            << "\tExpected: " << expected_output << '\n'
            << "\tOutput: " << output << '\n'
            << "\tCorrect?: " << std::boolalpha << is_correct << '\n'
            << "\tExecution time: " << execution_time << " ms\n"
            << "===========================================\n";
        total_time += execution_time;
        num_correct += is_correct;
    }

    std::cout
        << "Summary\n"
        << "\tCorrect answers: " << num_correct << '/' << solutions.size() << '\n'
        << "\tTotal time: " << total_time << " ms\n";
    std::cout << std::flush;
}
