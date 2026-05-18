#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H

#include <vector>
#include <string>

#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager {

private:
    std::vector<Movie> movies;

public:

    void addMovie(const Movie& movie);

    Movie* findMovieById(int id);

    Movie* findMovieByTitle(
        const std::string& title
    );

    void printAllMovies() const;

    void sortMoviesById();

    void sortMoviesByRating();

    int getMovieCount() const;

    // BaseManager override
    void loadFromFile(
        const std::string& filename
    ) override;

    void saveToFile(
        const std::string& filename
    ) const override;

    int size() const override;
};

#endif