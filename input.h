#pragma once
#include <string>

// Owner: Member A
int         readInt(const std::string& prompt, int minVal, int maxVal);
char        readRow(const std::string& prompt);      // returns 'A' to 'J'
bool        readYesNo(const std::string& prompt);
std::string readLine(const std::string& prompt);

