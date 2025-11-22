#pragma once

// #include "cli/parser.hpp"
#include "matrix.hpp"

#include <map>
#include <string>
#include <tabulate/table.hpp>

class Engine {
  public:
    Engine();
    void run();

  private:
    std::map<std::string, Matrix> matrices;
    tabulate::Table get_matrix_table();
    void pause_console();
};
