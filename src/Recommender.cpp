#include "Recommender.h"
#include "SimilarityCalculator.h" 
#include <cstdlib>   
#include <algorithm> 
#include <set>
#include <map>
#include <iostream>

Recommender::Recommender(const RatingManager& rm) : ratingManager(rm) {}

int Recommender::Similaritycalculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB) {
    return SimilarityCalculator::calculate(ratingsA, ratingsB);
}

std::vector<int> Recommender::recommend(int targetUserId, int K, int N) {
    std::vector<int> recommendedMovies;

    std::vector<Rating> myRatings = ratingManager.findByUser(targetUserId); 
    
    if (myRatings.empty()) {
        std::cerr << "[Notice] 유저 " << targetUserId << " 번의 평점 데이터가 부족하여 추천을 생성할 수 없습니다.\n";
        return recommendedMovies; 
    }

    std::set<int> myMovieIds;
    for (const Rating& r : myRatings) {
        myMovieIds.insert(r.getMovieId());
    }

    std::vector<std::pair<int, int>> userSimilarities; 
    std::vector<int> allUserIds = ratingManager.getAllUserIds();

    for (int otherId : allUserIds) {
        if (otherId == targetUserId) continue; 

        std::vector<Rating> otherRatings = ratingManager.findByUser(otherId);
        int simScore = Similaritycalculate(myRatings, otherRatings);
        userSimilarities.push_back({otherId, simScore});
    }

    std::sort(userSimilarities.begin(), userSimilarities.end(), 
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              });

    std::cout << "\n--- 유사도 계산 결과 ---\n";
    std::cout << " 기준 User " << targetUserId << "\n\n";
    for (size_t i = 0; i < userSimilarities.size() && i < (size_t)K; ++i) {
        if (userSimilarities[i].second == -100) continue;
        std::cout << "  User " << userSimilarities[i].first << " : " << userSimilarities[i].second << "\n";
    }
    if (!userSimilarities.empty() && userSimilarities[0].second != -100) {
        std::cout << " → User " << targetUserId << "과 가장 비슷한 사람: User " << userSimilarities[0].first << "\n";
    }

    int actualK = std::min(K, static_cast<int>(userSimilarities.size()));

    std::map<int, int> movieScores; 

    for (int i = 0; i < actualK; ++i) {
        if (userSimilarities[i].second == -100) continue; 

        int simUserId = userSimilarities[i].first;
        std::vector<Rating> simUserRatings = ratingManager.findByUser(simUserId);

        for (const Rating& r : simUserRatings) {
            if (myMovieIds.find(r.getMovieId()) == myMovieIds.end()) {
                movieScores[r.getMovieId()] += r.getScore();
            }
        }
    }

    if (movieScores.empty()) {
        return recommendedMovies;
    }

    std::vector<std::pair<int, int>> sortedMovies(movieScores.begin(), movieScores.end());
    std::sort(sortedMovies.begin(), sortedMovies.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              });

    int actualN = std::min(N, static_cast<int>(sortedMovies.size()));
    for (int i = 0; i < actualN; ++i) {
        recommendedMovies.push_back(sortedMovies[i].first);
    }

    return recommendedMovies;
}