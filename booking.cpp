// Owner: Member A  (see plan section 7.3)
#include "booking.h"
#include <iostream>
#include "common.h"
#include "input.h"
#include "movie.h"
#include "seat.h"
#include "ticket.h"
#include "payment.h"
using namespace std;

// Step counter: 0 goes one step back, a valid choice goes one step forward.
// One code path for every genre .
enum Step { GENRE, MOVIE, SHOWTIME, SEAT, PAYMENT };

void runBookMovie() {
    vector<Movie> all = loadMovies("data.csv");
    if (all.empty()) {
        cout << "No movies available.\n";
        return;
    }
    vector<string> genres = getGenres();

    vector<Movie> list;
    Movie movie;
    int slot = 1;
    string showKey;
    char row = 'A';
    int num = 1;

    Step step = GENRE;
    while (step != PAYMENT) {
        if (step == GENRE) {
            cout << "\n--- Choose a genre ---\n";
            for (int i = 0; i < genres.size(); i++)
                cout << (i + 1) << ". " << genres[i] << "\n";
            int g = readInt("Choose genre (0 = back to menu): ", 0, static_cast<int>(genres.size()));
            if (g == 0) return;
            list = filterByGenre(all, genres[g - 1]);
            if (list.empty()) {
                cout << "No movies in this genre.\n";
            } else {
                step = MOVIE;
            }
        }
        else if (step == MOVIE) {
            cout << "\n--- Choose a movie ---\n";
            printMovies(list);
            int m = readInt("Choose movie (0 = back): ", 0, static_cast<int>(list.size()));
            if (m == 0) {
                step = GENRE;
            } else {
                movie = list[m - 1];
                step = SHOWTIME;
            }
        }
        else if (step == SHOWTIME) {
            cout << "\n--- " << movie.name << ": choose a show time ---\n";
            cout << "1. " << movie.time[0] << " on " << movie.date[0] << "\n";
            cout << "2. " << movie.time[1] << " on " << movie.date[1] << "\n";
            int s = readInt("Choose show time (0 = back): ", 0, 2);
            if (s == 0) {
                step = MOVIE;
            } else {
                slot = s;
                showKey = makeShowKey(movie.id, slot);
                step = SEAT;
            }
        }
        else if (step == SEAT) {
            cout << "\n--- Choose a seat ---\n";
            printSeats(showKey);
            row = readRow("Row (A-J): ");
            num = readInt("Seat number (1-10): ", 1, 10);
            if (!isSeatFree(showKey, row, num)) {
                cout << "Seat " << row << num << " is already taken. Please choose another.\n";
            } else {
                step = PAYMENT;
            }
        }
    }

    // Booking details chosen: pay first, mark the seat only after payment succeeds.
    if (!processPayment(TICKET_PRICE)) {
        cout << "Payment cancelled. Your seat was not booked.\n";
        return;
    }
    if (!bookSeat(showKey, row, num)) {
        cout << "Sorry, that seat was just taken. Please try again.\n";
        return;
    }

    Booking b;
    b.movieName = movie.name;
    b.time      = movie.time[slot - 1];
    b.date      = movie.date[slot - 1];
    b.row       = row;
    b.seatNum   = num;
    b.ticketId  = generateTicketId(b.date);

    if (!saveBooking(b)) {
        cout << "Warning: could not save your booking to ticketStorage.csv.\n";
    }
    printTicket(b);
}
