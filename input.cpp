// Owner: Member A  (real code, see plan section 7.1)
// Written for real because both members use it.
#include "input.h"
#include <iostream>
#include <cctype>

// Reads a whole line; exits cleanly if input is closed (Ctrl+D / Ctrl+Z).
static std::string getInputLine() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cout << "\nInput closed. Exiting.\n";
        std::exit(0);
    }
    return line;
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    return getInputLine();
}

int readInt(const std::string& prompt, int minVal, int maxVal) {
    while (true) {
        std::string line = readLine(prompt);

        bool ok = !line.empty() && line.size() <= 9;   // 9 digits max, avoids overflow
        for (char c : line) {
            if (!std::isdigit(static_cast<unsigned char>(c))) ok = false;
        }

        if (ok) {
            int value = std::stoi(line);
            if (value >= minVal && value <= maxVal) return value;
        }
        std::cout << "Invalid input.\n";
    }
}

char readRow(const std::string& prompt) {
    while (true) {
        std::string line = readLine(prompt);
        if (line.size() == 1) {
            char c = static_cast<char>(std::toupper(static_cast<unsigned char>(line[0])));
            if (c >= 'A' && c <= 'J') return c;
        }
        std::cout << "Invalid input.\n";
    }
}

bool readYesNo(const std::string& prompt) {
    while (true) {
        std::string line = readLine(prompt);
        if (line == "Y" || line == "y") return true;
        if (line == "N" || line == "n") return false;
        std::cout << "Invalid input. Enter Y or N.\n";
    }
}
