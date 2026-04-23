#include "MovieManager.h"
#include <iostream>
#include <algorithm>

void MovieManager::addMovie(const Movie& movie) {

    for (const auto& m : movies) {

        if (m.getId() == movie.getId()) {

            std::cout << "[오류] ID " << movie.getId() << "번 영화가 이미 존재합니다.\n";

            return;

        }

    }

    movies.push_back(movie);

}

Movie* MovieManager::findMovieByTitle(const std::string& title) {
    for (auto& movie : movies) {
        if (movie.getTitle() == title) return &movie;
    }
    return nullptr;
}

Movie* MovieManager::findMovieById(int id) {
    for (auto& movie : movies) {
        if (movie.getId() == id) {
            return &movie; 
        }
    }
    return nullptr; 
}

void MovieManager::printAllMovies() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    for (const auto& movie : movies) {
        std::cout << movie << std::endl;
    }
}

void MovieManager::sortMoviesByRating() {

    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {

        return a.getAverageRating() > b.getAverageRating();

    });

}

void MovieManager::sortMoviesById() {

    std::sort(movies.begin(), movies.end());

    std::cout << "영화 목록이 ID순으로 정렬되었습니다.\n";

}

int MovieManager::getMovieCount() const {
    return (int)movies.size();
}