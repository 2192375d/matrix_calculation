#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

/*
 *
 * The function pauses the CLI and awaits for an enter to proceed
 */
inline void pause_console() {
    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
 * Return the number of digit of the given number.
 * The decimal point is considered as a digit as well.
 */
inline int get_num_digit(double n) {

    int numDigit = 0;

    if (n < 0) {
        numDigit++;
    }

    n = std::abs(n);

    // Special case n = 0 or n is null (printed as "?"), the number of digit is
    // 1
    if (n == 0) {
        return 1;
    }

    // When the number is an integer
    else if (n == int(n)) {

        int x = n;

        while (x != 0) {
            x /= 10;
            numDigit++;
        }
    }

    // When the number is a decimal
    else {
        std::string s = std::to_string(n);

        for (int i = s.size() - 1; s[i] == '0'; i--) {
            s.pop_back();
        }

        numDigit += s.size();
    }

    // Return it!
    return numDigit;
}

/*
 * Use linear search to loop through each number
 * in the given matrix, find the one with the
 * largest number of digit and returns the number
 * of digit of it. Note that the decimal point is
 * considered as a digit as well.
 */
inline int get_largest_digit(std::vector<std::vector<double>> m) {
    int largest = 0;
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m[i].size(); j++) {
            if (largest < getNumDigit(m[i][j])) {
                largest = getNumDigit(m[i][j]);
            }
        }
    }

    return largest;
}

inline int get_largest_index(std::vector<double> v) {

    int largest_index = 0;
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] > v[largest_index]) {
            largest_index = i;
        }
    }

    return largest_index;
}

inline double get_largest(std::vector<double> v) {

    double largest = v[0];
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] > largest) {
            largest = v[i];
        }
    }

    return largest;
}
