#include "SimilarityCalculator.h"
#include <cstdlib> 

int SimilarityCalculator::calculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB) {
    int commonCount = 0;
    int scoreDiffSum = 0;

    for (const Rating& rA : ratingsA) {
        for (const Rating& rB : ratingsB) {
            if (rA.getMovieId() == rB.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(rA.getScore() - rB.getScore());
            }
        }
    }

    if (commonCount == 0) {
        return -100; 
    }

    return (commonCount * 10) - scoreDiffSum;
}