#pragma once
#include <string>
#include <vector>
#include "common.h"

// Owner: Member A
std::vector<Movie>       loadMovies(const std::string& file);
std::vector<std::string> getGenres();
std::vector<Movie>       filterByGenre(const std::vector<Movie>& all, const std::string& genre);
void                     printMovies(const std::vector<Movie>& list);
