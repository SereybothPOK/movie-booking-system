#pragma once
#include <string>

// Shared by everyone. Do not change without telling your teammate.

struct Movie {
    std::string id;        // 100002
    std::string genre;     // Horror, Action, Fantasy, Romance, Sci_Fi
    std::string name;      // IT
    int duration;          // minutes
    std::string time[2];   // showtime 1 and 2, e.g. 14:50
    std::string date[2];   // date for showtime 1 and 2
};

struct Booking {
    std::string ticketId;  // 24-June-2026-686
    std::string movieName;
    std::string time;
    std::string date;
    char row;              // A to J
    int seatNum;           // 1 to 10
};

const double TICKET_PRICE = 5.0;

