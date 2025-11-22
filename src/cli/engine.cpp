#include "cli/engine.hpp"
#include "cli/parser.hpp"
#include "helpers.hpp"
#include "square-matrix.hpp"

#include <replxx.hxx>
#include <tabulate/table.hpp>

#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>
#include <unistd.h>

Engine::Engine() {}

void Engine::run() {
    replxx::Replxx rx;
    std::string line;

    while (true) {
        rx.clear_screen();
        print_header();
        print_table();

        const char *input = rx.input(">>> ");
        if (!input) {
            break;
        }

        line = input;
        Command cmd = parser(line);
        handle_command(cmd);

        rx.history_add(line);
    }
}

void Engine::handle_command(const Command &cmd) {

    if (cmd.type == Command_Type::Meta) {
        handle_meta(cmd);
        pause_console();
    }
    if (cmd.type == Command_Type::Operation) {
        handle_operation(cmd);
    }
    if (cmd.type == Command_Type::Invalid) {
        std::cout << "Invalid command\n";
        pause_console();
    }
}

void Engine::handle_meta(const Command &cmd) {
    const std::string &op = cmd.operation;
    if (op == "help") {
        std::cout << "Commands:\n"
                  << "  def <name>      define a matrix\n"
                  << "  det <name>      determinant of a stored matrix\n"
                  << "  list            list matrices\n"
                  << "  exit/quit       exit\n";
        return;
    }
    std::cout << "Unknown meta command: " << op << "\n";
}

void Engine::handle_operation(const Command &cmd) {
    const std::string &op = cmd.operation;
    if (op == "def") {
        if (cmd.args.size() != 1) {
            std::cout << "Usage: def <name>\n";
            return;
        }
        matrices_[cmd.args[0]] = prompt_matrix(cmd.args[0], false);
        return;
    }

    if (op == "det") {
        if (cmd.args.size() != 1) {
            std::cout << "Usage: det <name>\n";
            return;
        }
        auto it = matrices_.find(cmd.args[0]);
        if (it == matrices_.end()) {
            std::cout << "Matrix not found: " << cmd.args[0] << "\n";
            return;
        }
        try {
            Square_Matrix sm(it->second);
            std::cout << "det(" << cmd.args[0] << ") = " << sm.determinant()
                      << "\n";
        } catch (const std::exception &ex) {
            std::cout << "Error: " << ex.what() << "\n";
        }
        return;
    }

    std::cout << "Unsupported operation: " << op << "\n";
}

tabulate::Table Engine::build_matrix_table() const {
    tabulate::Table table;
    table.format()
        .corner_color(tabulate::Color::blue)
        .border_color(tabulate::Color::blue);

    for (const auto &pair : matrices_) {
        std::stringstream ss;
        ss << pair.second;
        auto &row = table.add_row({pair.first, ss.str()});
        row.format().font_color(tabulate::Color::cyan);
    }

    return table;
}

void Engine::print_header() const {
    std::cout << "_______________MATRIX CALCULATOR_______________\n";
}

void Engine::print_table() const {
    tabulate::Table table = build_matrix_table();
    if (table.size() > 0) {
        std::cout << table << "\n";
    }
}

Matrix Engine::prompt_matrix(const std::string &name,
                             bool force_square = false) const {
    size_t rows = prompt_size("Enter the number of rows: ");
    size_t cols = prompt_size("Enter the number of columns: ");

    if (force_square && rows != cols) {
        size_t n = std::min(rows, cols);
        rows = cols = n;
    }

    std::vector<std::vector<double>> data(rows, std::vector<double>(cols, 0.0));
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            data[r][c] = prompt_entry(r, c);
        }
    }

    try {
        return Matrix(data);
    } catch (const std::exception &ex) {
        std::cout << "Failed to create matrix " << name << ": " << ex.what()
                  << "\n";
        return Matrix();
    }
}

size_t Engine::prompt_size(const std::string &label) const {
    while (true) {
        std::cout << label << std::flush;
        size_t n = 0;
        if (std::cin >> n) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return n;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a positive integer.\n";
    }
}

double Engine::prompt_entry(size_t r, size_t c) const {
    while (true) {
        std::cout << "Enter entry at [" << r << "][" << c
                  << "]: " << std::flush;
        double val = 0.0;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a number.\n";
    }
}
