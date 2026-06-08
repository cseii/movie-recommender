#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <vector>
#include <string> // 추가
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

    bool loadFromCSV(const std::string& filename, RatingManager& mutableRm);
    bool saveToCSV(const std::string& filename) const;

    void printStatics() const;
};

#endif