#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <vector>
#include "RatingManager.h"
#include "Rating.h"

class Recommender {
private:
    const RatingManager& ratingManager;

public:
    Recommender(const RatingManager& rm);

    int Similaritycalculate(
        const std::vector<Rating>& ratingsA,
        const std::vector<Rating>& ratingsB
    );

    std::vector<int> recommend(int targetUserId, int K, int N);
};

#endif