#include "helpers.hpp"
#include "matrix.hpp"
#include "square-matrix.hpp"
#include "triangular-matrix.hpp"

#include <ostream>
#include <replxx.hxx>
#include <tabulate/table.hpp>

#include <cmath>
#include <exception>
#include <iostream>
#include <map>
#include <string>

constexpr auto DARK_BLUE = "\033[34m";
constexpr auto LIGHT_BLUE = "\033[94m";
constexpr auto ORANGE = "\033[38;5;208m";

constexpr auto RESET = "\033[0m";

void change_colour(std::string colour_string) { std::cout << colour_string; }

int main() {

    replxx::Replxx rx;
    std::map<std::string, Matrix> matrices;
    tabulate::Table matrix_table;

    matrices["A"] = Matrix({{1, 2, 3}, {2, 4, 1}, {-1, 2, 1}});

    while (true) {
        matrix_table.format()
            .corner_color(tabulate::Color::blue)
            .border_color(tabulate::Color::blue);

        for (std::map<std::string, Matrix>::iterator it = matrices.begin();
             it != matrices.end(); it++) {
            auto &row = matrix_table.add_row(tabulate::RowStream{}
                                             << it->first << it->second);
            row.format().font_color(tabulate::Color::cyan);
        }

        std::cout << DARK_BLUE
                  << "_______________MATRIX CALCULATOR_______________" << RESET
                  << std::endl;

        std::cout << matrix_table;

        const char *input = rx.input(">>> ");
        if (!input)
            break;

        std::string line(input);
        if (line == "exit" or line == "quit") {
            break;
        }

        rx.history_add(line);
        rx.clear_screen();
    }

    return 0;
}
