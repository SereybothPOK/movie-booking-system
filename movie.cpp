// Owner: Member A  (see plan section 7.2)
#include "movie.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Remove a trailing '\r' (file edited on Windows) and surrounding spaces.
static string trim(string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' ' || s.back() == '\t'))
        s.pop_back();
    size_t start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\t')) start++;
    return s.substr(start);
}

// Read data.csv: skip header, split each line on commas into 8 fields.
vector<Movie> loadMovies(const string& file) {
    vector<Movie> movies;

    ifstream in(file);
    if (!in) {
        cout << "Error: cannot open " << file << ". Run the program from the folder that contains it.\n";
        return movies;
    }

    string line;
    getline(in, line);                       // discard header

    while (getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;

        vector<string> f;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) f.push_back(trim(field));
        if (f.size() < 8) continue;               // malformed line

        Movie m;
        m.id       = f[0];
        m.genre    = f[1];
        m.name     = f[2];
        try {
            m.duration = stoi(f[3]);
        } catch (...) {
            continue;                             // bad duration, skip line
        }
        m.time[0] = f[4];  m.time[1] = f[5];
        m.date[0] = f[6];  m.date[1] = f[7];
        movies.push_back(m);
    }
    return movies;
}

// Already done, nothing to change here.
vector<string> getGenres() {
    return {"Horror", "Action", "Fantasy", "Romance", "Sci_Fi"};
}

// Copy only the movies whose genre matches.
vector<Movie> filterByGenre(const vector<Movie>& all, const string& genre) {
    vector<Movie> result;
    for (const Movie& m : all) {
        if (m.genre == genre) result.push_back(m);
    }
    return result;
}

// 1. name | duration mins | time1 on date1 | time2 on date2
void printMovies(const vector<Movie>& list) {
    for (int i = 0; i < list.size(); i++) {
        const Movie& m = list[i];
        cout << (i + 1) << ". " << m.name << " | " << m.duration << " mins | " << m.time[0] 
        << " on " << m.date[0] << " | "<< m.time[1] << " on " << m.date[1] << "\n";
    }
}
