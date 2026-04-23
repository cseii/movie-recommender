#pragma once
#include <vector>
#include "rating.h"
#include "MovieManager.h"

class RatingManager {
private:
    std::vector<Rating> ratings;

public:
    void addRating(const Rating& rating, MovieManager& movieManager);
    void printAllRatings() const;
};