#pragma once

// #include "cli/parser.hpp"
#include "matrix.hpp"

#include <map>
#include <string>
#include <tabulate/table.hpp>

class Engine {
  public:
    std::map<std::string, Matrix> matrices;

    Engine();

    tabulate::Table get_matrix_table();
    void run();
};
