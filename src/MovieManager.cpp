#include "MovieManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm> 

void MovieManager::addMovie(const Movie& movie) {
    movies.push_back(movie);
}

void MovieManager::sortMoviesById() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.getId() < b.getId();
    });
    std::cout << "영화 목록이 ID순으로 정렬되었습니다.\n";
}

void MovieManager::sortMoviesByRating() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.getAverageRating() > b.getAverageRating(); 
    });
    std::cout << "영화 목록이 평점순으로 정렬되었습니다.\n";
}

Movie* MovieManager::findMovieByTitle(const std::string& title) {
    for (size_t i = 0; i < movies.size(); ++i) {
        if (movies[i].getTitle() == title) {
            return &movies[i];     // 원본 데이터의 주소값 리턴
        }
    }
    return nullptr; 
}

Movie* MovieManager::findMovieById(int id) {
    for (size_t i = 0; i < movies.size(); ++i) {
        if (movies[i].getId() == id) {
            return &movies[i];
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
        std::cout << movie << "\n";
    }
}

int MovieManager::size() const {
    return movies.size();
}

bool MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line, header;
    if (std::getline(file, header)) {}   // 헤더 스킵

    while (std::getline(file, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
            line.pop_back();             
        }
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, title, genre, yearStr;

        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, title, ',') &&
            std::getline(ss, genre, ',') &&
            std::getline(ss, yearStr)) {
            
            try {
                int id = std::stoi(idStr);
                int year = std::stoi(yearStr);
                movies.push_back(Movie(id, title, genre, year));
            } catch (...) {
                continue; 
            }
        }
    }
    file.close();
    return true; 
}

bool MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "id,title,genre,year\n";
    for (const auto& movie : movies) {
        file << movie.getId() << "," 
             << movie.getTitle() << "," 
             << movie.getGenre() << "," 
             << movie.getReleaseYear() << "\n";
    }
    file.close();
    return true;
}