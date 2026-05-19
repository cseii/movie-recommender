#ifndef SIMILARITY_CALCULATOR_H
#define SIMILARITY_CALCULATOR_H

#include <vector>
#include "Rating.h"

class SimilarityCalculator {
public:
    static int calculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB);
};

#endif