#include "seat.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>  //to classify and convert individual characters without manually writing ASCII range checks. 
#include <string>

const int ROWS = 10;
const int COLS = 10;

//create a file for each movie + showtime
std::string seatFileName(const std::string& showKey) {
    return "seats_" + showKey + ".txt";
}

//writes the grid back to the file
void saveSeats(const std::string& showKey, const std::vector<std::string>& grid) {
    std::ofstream file(seatFileName(showKey));
    for (int r = 0; r < ROWS; r++) {
        file << grid[r] << "\n";
    }
}

//loadSeats reads the file into a grid. 
std::vector<std::string> loadSeats(const std::string& showKey) {
    std::vector<std::string> grid;

    std::ifstream file(seatFileName(showKey));
    if (file.is_open()) {
        // the file exists: read every line into the grid
        std::string line;
        while (std::getline(file, line)) {
            grid.push_back(line);
        }
    } else {
        // the file does not exist yet: start with 10 rows of free seats
        for (int r = 0; r < ROWS; r++) {
            grid.push_back("OOOOOOOOOO");
        }
        saveSeats(showKey, grid);
    }
    return grid;
}

std::string makeShowKey(const std::string& movieId, int slot) {
    return movieId + "_" + std::to_string(slot);
}
//to_string converts a number into text


void printSeats(const std::string& showKey) {
    std::vector<std::string> grid = loadSeats(showKey);
    std::string letters = "ABCDEFGHIJ";

    // top line: the seat numbers 1 to 10
    std::cout << "\n   ";
    for (int c = 1; c <= 10; c++) {
        if (c < 10) std::cout << "  ";   // two spaces before a one-digit number
        else        std::cout << " ";    // one space before 10
        std::cout << c << " ";
    }
    std::cout << "\n";

    // one line for each row A to J
    for (int r = 0; r < 10; r++) {
        std::cout << letters[r] << ": ";
        for (int c = 0; c < 10; c++) {
            if (grid[r][c] == 'X') {
                std::cout << "[ X]";
            } else if (c + 1 < 10) {
                std::cout << "[ " << c + 1 << "]";
            } else {
                std::cout << "[" << c + 1 << "]";
            }
        }
        std::cout << "\n";
    }
    std::cout << "[X] = taken\n";
}

bool isSeatFree(const std::string& showKey, char row, int num) {
    int r = row - 'A';    // A = 0, B = 1, ... J = 9
    int c = num - 1;      // seat 1 = 0, seat 2 = 1, ... seat 10 = 9

    // the seat must exist: rows A to J, seats 1 to 10
    if (r < 0 || r > 9 || c < 0 || c > 9) {
        return false;
    }

    std::vector<std::string> grid = loadSeats(showKey);
    if (grid[r][c] == 'O') {
        return true;     // free
    } else {
        return false;    // taken
    }
}



//bookSeat changes one character in the grid
bool bookSeat(const std::string& showKey, char row, int num) {
    row = std::toupper(row);
    // 1. check the seat first: it must exist and must be free
    if (isSeatFree(showKey, row, num) == false) {
        return false;
    }

    // 2. turn the seat name (like A3) into grid positions
    int r = row - 'A';    // A = 0, B = 1, ... J = 9
    int c = num - 1;      // seat 1 = 0, seat 2 = 1, ... seat 10 = 9

    // 3. load the grid, mark the seat as taken, save it back to the file
    std::vector<std::string> grid = loadSeats(showKey);
    grid[r][c] = 'X';
    saveSeats(showKey, grid);

    return true;          // booking worked
}

