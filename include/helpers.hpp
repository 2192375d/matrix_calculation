#pragma once

#include <iostream>
#include <limits>

/*
 *
 * The function pauses the CLI and awaits for an enter to proceed
 */
inline void pause_console() {
    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
