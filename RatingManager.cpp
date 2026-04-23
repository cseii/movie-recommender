#include "RatingManager.h"
#include <iostream>

void RatingManager::addRating(const Rating& rating, MovieManager& movieManager) {
    Movie* movie = movieManager.findMovieById(rating.getMovieId());
    if (movie == nullptr) {
        std::cout << "[오류] ID " << rating.getMovieId() << "번 영화를 찾을 수 없어 평점을 등록할 수 없습니다.\n";
        return;
    }

    ratings.push_back(rating);

    movie->addRating(rating.getScore());
    std::cout << "평점이 성공적으로 등록되었습니다.\n";
}

void RatingManager::printAllRatings() const {
    for (const auto& r : ratings) {
        r.display();
    }
}