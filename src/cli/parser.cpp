#include "cli/parser.hpp"
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

constexpr char SPACE = 32;
constexpr char SYMBOLS[] = {':', '=', '+', '-', '*'};
const std::string OPERATIONS[] = {"def", "det", "solve"};

std::vector<std::string> tokenize(std::string message) {

    int previous_index = 0;
    std::vector<std::string> result;
    size_t count = 0;

    while (previous_index < message.size() &&
           message[previous_index] == SPACE) {
        previous_index++;
    }

    while (count + previous_index < message.size()) {

        if (message[count + previous_index] == SPACE) {

            result.push_back(message.substr(previous_index, count));
            previous_index = previous_index + count;

            while (previous_index < message.size() &&
                   message[previous_index] == SPACE) {
                previous_index++;
            }

            count = 0;
            continue;
        }

        if (std::find(std::begin(SYMBOLS), std::end(SYMBOLS),
                      message[count + previous_index]) != std::end(SYMBOLS)) {
            result.push_back(std::string(1, message[count + previous_index]));

            previous_index += count + 1;

            while (previous_index < message.size() &&
                   message[previous_index] == SPACE) {
                previous_index++;
            }

            count = 0;
            continue;
        }

        count++;
    }

    if (count > 0) {
        result.push_back(message.substr(previous_index, count));
    }

    return result;
}

Command parser(std::string message) {

    std::vector<std::string> tokens = tokenize(message);

    if (tokens.empty()) {
        return {Command_Type::Invalid, "", {}};
    }

    Command cmd;

    // handle Meta, eg :help
    if (tokens[0] == std::string(1, SYMBOLS[0])) {
        if (tokens.size() < 2) {
            return {Command_Type::Meta, "", {}};
        }

        cmd.type = Command_Type::Meta;
        cmd.operation = tokens[1];
        for (size_t i = 2; i < tokens.size(); i++) {
            cmd.args.push_back(tokens[i]);
        }

        return cmd;
    }

    // handle basic OPERATIONS, eg def
    if (std::find(std::begin(OPERATIONS), std::end(OPERATIONS), tokens[0]) !=
        std::end(OPERATIONS)) {

        if (tokens.size() < 2) {
            return {Command_Type::Invalid, tokens[0], {}};
        }

        cmd.type = Command_Type::Operation;
        cmd.operation = tokens[0];
        for (size_t i = 1; i < tokens.size(); i++) {
            cmd.args.push_back(tokens[i]);
        }

        return cmd;
    }

    // handle = + - *
    if (tokens.size() >= 2 && !tokens[1].empty() &&
        std::find(std::begin(SYMBOLS), std::end(SYMBOLS), tokens[1][0]) !=
            std::end(SYMBOLS)) {
        cmd.args.push_back(tokens[0]);
        for (size_t i = 2; i < tokens.size(); i++) {
            cmd.args.push_back(tokens[i]);
        }
        cmd.operation = tokens[1];

        cmd.type = Command_Type::Operation;
        if (tokens.size() != 3) {
            cmd.type = Command_Type::Invalid;
        }
        return cmd;
    }

    return {Command_Type::Invalid, "", tokens};
}
