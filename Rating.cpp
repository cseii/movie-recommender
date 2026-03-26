#include "Rating.h"
#include <iostream>

Rating::Rating(int uId, int mId, double s);
    : userId(uId), movieId(mId) {
        if (s < 0.0 || s > 5.0) {
            std::cout << "[Rating Error] Invalid score" << s << ". Setting to 0.0" << std:
            score = 0.0;
        } else {
            score = s;
        }
}

int Rating::getUser() const { return userId; }
int Rating::getMovieId() const { return movieId; }
double Rating::getScore() const { return score; }

void Rating::display() const {
    std::cout << "Rating Info -> User: " <<userId
              << ", Movie: " << movieId
              << ", Score: " << score << std::endl;
}