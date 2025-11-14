#include "cli/engine.hpp"

#include <replxx.hxx>
#include <tabulate/table.hpp>

#include <iostream>

constexpr auto DARK_BLUE = "\033[34m";
constexpr auto LIGHT_BLUE = "\033[94m";
constexpr auto ORANGE = "\033[38;5;208m";

constexpr auto RESET = "\033[0m";

Engine::Engine() {}

void Engine::run() {

    replxx::Replxx rx;
    bool running = true;
    tabulate::Table t;

    t.format()
        .corner_color(tabulate::Color::blue)
        .border_color(tabulate::Color::blue);

    while (running) {
        t = get_matrix_table();

        std::cout << RESET << "_______________MATRIX CALCULATOR_______________"
                  << std::endl;
        std::cout << t;

        const char *input = rx.input(">>> ");

        if (input == NULL) {
            break;
        }

        std::string line(input);

        if (line == "exit") {
            break;
        }
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
