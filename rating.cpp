#include "Rating.h"
#include <iostream>

Rating::Rating() : userId(0), movieId(0), score(0.0) {}

Rating::Rating(int uId, int mId, double s)
    : userId(uId), movieId(mId) {
    if (s < 0.0 || s > 5.0) {
        std::cout << "[Rating Error] Invalid score. Setting to 0.0" << std::endl;
        score = 0.0;
    } else {
        score = s;
    }
}

int    Rating::getUserId()  const { return userId; }
int    Rating::getMovieId() const { return movieId; }
double Rating::getScore()   const { return score; }

std::ostream& operator<<(std::ostream& os, const Rating& rating) {
    os << "User " << rating.userId << " -> Movie " << rating.movieId 
       << " | Score: " << rating.score;
    return os;
}

void Rating::display() const {
    std::cout << *this << std::endl;
}