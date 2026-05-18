#include "Recommender.h"
#include <cstdlib>   // std::abs
#include <algorithm> // std::sort, std::min
#include <set>
#include <map>
#include <iostream>

Recommender::Recommender(const RatingManager& rm) : ratingManager(rm) {}

// 교수님이 주신 공식 기반 유사도 계산
int Recommender::Similaritycalculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB) {
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

    // 엣지 케이스 1: 공통으로 본 영화가 전혀 없을 때
    if (commonCount == 0) {
        return -100; 
    }

    return commonCount * 10 - scoreDiffSum;
}

// 5단계 추천 프로세스 흐름
std::vector<int> Recommender::recommend(int targetUserId, int K, int N) {
    std::vector<int> recommendedMovies;

    // 1단계: 대상 사용자의 평점 목록 조회
    std::vector<Rating> myRatings = ratingManager.findByUser(targetUserId);
    
    // 엣지 케이스 2: 추천 대상자가 평가를 내린 기록이 아예 없는 신규 유저일 때
    if (myRatings.empty()) {
        std::cerr << "[Notice] 유저 " << targetUserId << " 번의 평점 데이터가 부족하여 추천을 생성할 수 없습니다.\n";
        return recommendedMovies; 
    }

    // 중복 제거 및 빠른 탐색을 위해 이미 본 영화 ID를 set에 보관
    std::set<int> myMovieIds;
    for (const Rating& r : myRatings) {
        myMovieIds.insert(r.getMovieId());
    }

    // 2단계: 다른 모든 사용자와의 유사도 계산
    std::vector<std::pair<int, int>> userSimilarities; // (userId, similarityScore)
    std::vector<int> allUserIds = ratingManager.getAllUserIds();

    for (int otherId : allUserIds) {
        if (otherId == targetUserId) continue; // 자기 자신 제외

        std::vector<Rating> otherRatings = ratingManager.findByUser(otherId);
        int simScore = Similaritycalculate(myRatings, otherRatings);
        userSimilarities.push_back({otherId, simScore});
    }

    // 3단계: 유사도 기준 내림차순 정렬 (람다 함수 활용)
    std::sort(userSimilarities.begin(), userSimilarities.end(), 
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              });

    // 전체 유저 수가 요청한 K명보다 작을 수 있으므로 경계 설정
    int actualK = std::min(K, static_cast<int>(userSimilarities.size()));

    // 4단계 & 5단계: 상위 K명의 평점을 기반으로 영화 추천 점수 합산
    std::map<int, int> movieScores; // (movieId, 누적 스코어)

    for (int i = 0; i < actualK; ++i) {
        if (userSimilarities[i].second == -100) continue; // 공통 영화가 없는 유저는 후보 탈락

        int simUserId = userSimilarities[i].first;
        std::vector<Rating> simUserRatings = ratingManager.findByUser(simUserId);

        for (const Rating& r : simUserRatings) {
            // 내가 아직 보지 않은 영화만 추천 대상으로 분류
            if (myMovieIds.find(r.getMovieId()) == myMovieIds.end()) {
                movieScores[r.getMovieId()] += r.getScore();
            }
        }
    }

    // 엣지 케이스 3: 주변 이웃들이 본 영화 중 내가 안 본 영화 후보가 아예 없는 경우
    if (movieScores.empty()) {
        return recommendedMovies;
    }

    // 결과를 점수가 높은 순으로 재정렬하기 위해 vector로 복사
    std::vector<std::pair<int, int>> sortedMovies(movieScores.begin(), movieScores.end());
    std::sort(sortedMovies.begin(), sortedMovies.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              });

    // 최종 상위 N개 추출하여 리스트업
    int actualN = std::min(N, static_cast<int>(sortedMovies.size()));
    for (int i = 0; i < actualN; ++i) {
        recommendedMovies.push_back(sortedMovies[i].first);
    }

    return recommendedMovies;
}