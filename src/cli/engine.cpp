#include "cli/engine.hpp"
#include "cli/parser.hpp"

#include <replxx.hxx>
#include <tabulate/table.hpp>

#include <iostream>
#include <limits>
#include <map>

Engine::Engine() {}

void Engine::run() {

    replxx::Replxx rx;
    tabulate::Table t;
    Command cmd;
    std::string line_input;

    matrices["A"] = Matrix({{1, 2, 3}, {2, 4, 1}, {-1, 2, 1}});

    while (true) {
        rx.clear_screen();

        t = get_matrix_table();

        std::cout << "_______________MATRIX CALCULATOR_______________"
                  << std::endl;
        std::cout << t << std::endl;

        const char *INPUT = rx.input(">>> ");
        if (INPUT == NULL) {
            break;
        }
        line_input = INPUT;
        cmd = parser(line_input);

        // handle command using command.hpp
    }
}

tabulate::Table Engine::get_matrix_table() {
    tabulate::Table result;
    for (auto it = matrices.begin(); it != matrices.end(); it++) {
        auto &row =
            result.add_row(tabulate::RowStream{} << it->first << it->second);
        row.format().font_color(tabulate::Color::cyan);
    }

    return result;
}

void Engine::pause_console() {
    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
