#pragma once

#include "cli/parser.hpp"
#include "matrix.hpp"

#include <string>
#include <unordered_map>

class Engine {
  public:
    Engine();

    // Run the interactive loop (returns when user exits)
    int run();

  private:
    using MatrixStore = std::unordered_map<std::string, Matrix>;

    void execute(const Command &cmd);
    void handle_meta(const Command &cmd);
    void handle_operation(const Command &cmd);

    MatrixStore matrices_;
    bool running_;
};
