// Owner: Member A  (real code, see plan section 7.8)
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "input.h"
#include "booking.h"
#include "checkbooking.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));   // once, for ticket numbers

    while (true) {
        std::cout << "\n===== Movie Ticket Booking =====\n";
        std::cout << "1. Book a Movie\n";
        std::cout << "2. Check Booking\n";
        std::cout << "3. Exit\n";

        int choice = readInt("What would you like to do? ", 1, 3);

        if (choice == 1)      runBookMovie();
        else if (choice == 2) runCheckBooking();
        else                  break;
    }

    std::cout << "Goodbye!\n";
    return 0;
}
