#pragma once
#include <string>

// Owner: Member B
std::string makeShowKey(const std::string& movieId, int slot);   // e.g. 100002_1
void        printSeats(const std::string& showKey);
bool        isSeatFree(const std::string& showKey, char row, int num);
bool        bookSeat(const std::string& showKey, char row, int num);   // false if taken
