#pragma once
#include <string>
#include "common.h"

// Owner: Member B
std::string generateTicketId(const std::string& date);
bool        saveBooking(const Booking& b);
bool        findBooking(const std::string& ticketId, Booking& out);
void        printTicket(const Booking& b);
