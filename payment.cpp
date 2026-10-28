#include <iostream>
#include "payment.h"
#include "input.h"

bool processPayment(double amount) {
    std::cout << "\n--- Payment ---\n";
    std::cout << "Total: $" << amount << "\n";
    std::cout << "1. Cash\n";
    std::cout << "2. Card\n";
    std::cout << "3. E-wallet (Bakong/ ABA / Wing)\n";
    std::cout << "0. Cancel\n";

    int choice = readInt("Choose payment method: ", 0, 3);

    if (choice == 0) {
        std::cout << "Payment cancelled.\n";
        return false;
    }

    if (choice == 1) {
        std::cout << "Please pay $" << amount << " at the cashier.\n";
        return true;
    }

    std::cout << "Confirm payment of $" << amount << "\n";
    bool ok = readYesNo("Proceed? (Y/N): ");
    if (ok == true){
        std::cout << "Payment sucessful.\n";
        return true;
    }
    else{
        std::cout << "Payment cancelled.\n";
        return false;
    }
}

