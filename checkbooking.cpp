#include <iostream>
#include "checkbooking.h"
#include "ticket.h"
#include <string>

void runCheckBooking(){
    std::cout << "\n--- Check Booking ---\n";
    std::string id;
    std::cout << "Enter your Ticket Id: ";
    std::getline(std::cin, id);

    Booking b;
    if (findBooking(id, b) == true) {
        printTicket(b);
    }
    else{
        std::cout << "Ticket not found.\n";
    }
}
