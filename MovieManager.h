#pragma once
#include <vector>
#include <string>
#include "Movie.h"

class MovieManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie(const Movie& movie);

    Movie* findMovieById(int id);

    Movie* findMovieByTitle(const std::string& title);

    void printAllMovies() const;

    void sortMoviesById();

    void sortMoviesByRating();

    int getMovieCount() const;
};