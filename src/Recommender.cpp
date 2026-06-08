#include "Recommender.h"
#include "SimilarityCalculator.h" 
#include <cstdlib>   
#include <algorithm> 
#include <set>   // 중복 제거 및 빠른 탐색(find)을 위해
#include <map>   // 영화별 누적 추천 점수를 저장(Key-Value)하기 위해
#include <iostream>

// 생성자: 멤버 초기화 리스트를 통해 의존성 주입 형태로 RatingManager 참조자를 초기화
Recommender::Recommender(const RatingManager& rm) : ratingManager(rm) {}

int Recommender::Similaritycalculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB) {
    return SimilarityCalculator::calculate(ratingsA, ratingsB);
}

// 협업 필터링 추천 알고리즘 함수
std::vector<int> Recommender::recommend(int targetUserId, int K, int N) {
    std::vector<int> recommendedMovies;   // 최종 추천 결과(영화 ID 목록)를 담을 벡터

    // 타겟 유저의 평점 데이터 가져오기 및 엣지 케이스 방어
    std::vector<Rating> myRatings = ratingManager.findByUser(targetUserId); 
    
    if (myRatings.empty()) {   // 타겟 유저의 평점 이력이 없는 경우
        std::cerr << "[Notice] 유저 " << targetUserId << " 번의 평점 데이터가 부족하여 추천을 생성할 수 없습니다.\n";
        return recommendedMovies;   // 빈 벡터를 리턴하여 프로그램이 터지는 것 방지
    }

    // 타겟 유저가 이미 본 영화 ID를 set에 저장(필터링 준비)
    std::set<int> myMovieIds;
    for (const Rating& r : myRatings) {
        myMovieIds.insert(r.getMovieId());
    }

    // 모든 사용자들과의 유사도 계산 및 정렬(가장 유사한 K명 추출)
    std::vector<std::pair<int, int>> userSimilarities; 
    std::vector<int> allUserIds = ratingManager.getAllUserIds();

    for (int otherId : allUserIds) {
        if (otherId == targetUserId) continue;   // 나 자신과의 유사도 계산은 건너뜀

        std::vector<Rating> otherRatings = ratingManager.findByUser(otherId);
        int simScore = Similaritycalculate(myRatings, otherRatings);   // 유사도 계산 함수 호출
        userSimilarities.push_back({otherId, simScore});   // 벡터에 삽입
    }

    // 유사도 점수 기준 내림차순 정렬
    std::sort(userSimilarities.begin(), userSimilarities.end(), 
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              });

    // 디버깅 및 콘솔 시각화를 위한 중간 유사도 출력 로직
    std::cout << "\n--- 유사도 계산 결과 ---\n";
    std::cout << " 기준 User " << targetUserId << "\n\n";
    for (size_t i = 0; i < userSimilarities.size() && i < (size_t)K; ++i) {
        if (userSimilarities[i].second == -100) continue;   // 공통 영화가 없어 -100점인 유저는 출력 제외
        std::cout << "  User " << userSimilarities[i].first << " : " << userSimilarities[i].second << "\n";
    }
    if (!userSimilarities.empty() && userSimilarities[0].second != -100) {
        std::cout << " → User " << targetUserId << "과 가장 비슷한 사람: User " << userSimilarities[0].first << "\n";
    }

    // 유사한 상위 K명의 평점을 기반으로 영화 추천 점수 누적 계산
    // 요청한 K값이 전체 유저 수보다 클 수 있으므로 std::min을 사용해 바운더리 제한
    int actualK = std::min(K, static_cast<int>(userSimilarities.size()));

    std::map<int, double> movieScores; 

    for (int i = 0; i < actualK; ++i) {
        if (userSimilarities[i].second == -100) continue; 

        int simUserId = userSimilarities[i].first;
        std::vector<Rating> simUserRatings = ratingManager.findByUser(simUserId);

        for (const Rating& r : simUserRatings) {
            // 타겟 유저가 이미 본 영화 목록에 들어있지 않은 경우에만 점수 집계
            if (myMovieIds.find(r.getMovieId()) == myMovieIds.end()) {
                movieScores[r.getMovieId()] += r.getScore();   // 추천 영화 평점(double) 누적 합산
            }
        }
    }

    if (movieScores.empty()) {   // 추천가능한 영화가 없는 경우 방어
        return recommendedMovies;
    }

    std::vector<std::pair<int, double>> sortedMovies(movieScores.begin(), movieScores.end());
    std::sort(sortedMovies.begin(), sortedMovies.end(),
              [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                  return a.second > b.second;
              });

    int actualN = std::min(N, static_cast<int>(sortedMovies.size()));
    for (int i = 0; i < actualN; ++i) {
        recommendedMovies.push_back(sortedMovies[i].first);
    }

    return recommendedMovies;
}