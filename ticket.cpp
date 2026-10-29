#include "ticket.h"
#include <iostream>
#include <fstream>
#include <sstream> //convert strings into numbers, and numbers to string
#include <cstdlib> //for random number generation

// generate a ticket Id with teh format 24-June-2026-321 and see if it 
// not in used. otherwise, generate another ticket
std::string generateTicketId(const std::string& date){
    while (true) {
        int number = rand() % 900 + 100;
        std::string id = date + "-" + std::to_string(number);

        Booking temp;
        if (findBooking(id, temp) == false) {
            return id;
        }
    }
}

bool saveBooking(const Booking& b){
    std::ofstream file("ticketstorage.csv", std::ios::app);
    if (file.is_open() == false) {
        return false;
    }

    file << b.ticketId << ","
        << b.movieName << ","
        << b.time << ","
        << b.date << ","
        << b.row << ","
        << b.seatNum << "\n";

    return true;
}

bool findBooking(const std::string& ticketId, Booking& out){
    if (ticketId == "") {
        return false;
    }
    std::ifstream file("ticketStorage.csv");
    if (file.is_open() == false){
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream parts(line);
        std::string id, movie, time, date, rowText, seatText;
        std::getline(parts, id, ',');
        std::getline(parts, movie, ',');
        std::getline(parts, time, ',');
        std::getline(parts, date, ',');
        std::getline(parts, rowText, ',');
        std::getline(parts, seatText, ',');


    if (id == ticketId) {
        out.ticketId = id;
        out.movieName = movie;
        out.time = time;
        out.date = date;
        out.row = rowText[0]; // for converting the text to char
        out.seatNum = std::stoi(seatText);
        return true;
    }
}

    return false;
    //went through the file but couldn't find the ticket id
}

//show the ticket on the screen
void printTicket(const Booking& b){
    std::cout << "\n--- TICKET ---\n"
            << "Ticket Id: " << b.ticketId << "\n"
            << "Movie:     " << b.movieName << "\n"
            << "Time:      " << b.time << " on " << b.date << "\n"
            << "Seat:      " << b.row << b.seatNum << "\n";
}
