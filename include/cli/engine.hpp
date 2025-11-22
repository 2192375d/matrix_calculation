#pragma once

#include "cli/parser.hpp"
#include "matrix.hpp"

#include <map>
#include <string>
#include <tabulate/table.hpp>

class Engine {
  public:
    Engine();
    void run();

  private:
    using MatrixStore = std::map<std::string, Matrix>;

    MatrixStore matrices_;

    tabulate::Table build_matrix_table() const;
    void print_header() const;
    void print_table() const;

    void handle_command(const Command &cmd);
    void handle_meta(const Command &cmd);
    void handle_operation(const Command &cmd);

    Matrix prompt_matrix(const std::string &name, bool force_square) const;
    size_t prompt_size(const std::string &label) const;
    double prompt_entry(size_t r, size_t c) const;
};
