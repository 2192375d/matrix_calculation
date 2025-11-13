#pragma once

#include <string>
#include <vector>
enum class Command_Type { Meta, Operation, Invalid };

struct Command {
    Command_Type type;
    std::string operation;
    std::vector<std::string> args;
};

Command parser(std::string input);
