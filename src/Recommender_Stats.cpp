#include "Recommender.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <iomainp>

// ====================================================================
// 추가 기능 2: 영화별 평균 평점 Top N 산출 및 출력 함수
// ====================================================================
void Recommender::printStatistics() const {
    // 1. 생성자 시점에 주입받았던 ratingManager로부터 전체 평점 데이터 벡터를 가져옵니다.
    const std::vector<Rating>& allRatings = ratingManager.getRatings();
    
    // 만약 CSV 로드가 안 되었거나 평점 데이터가 없으면 경고 후 종료 (방어 코드)
    if (allRatings.empty()) {
        std::cout << "\n[Notice] 분석할 평점 데이터가 메모리에 존재하지 않습니다.\n";
        return;
    }

    // 화면에 보여주고 싶은 상위 영화 개수 설정 (Top 5)
    int N = 5; 

    std::cout << "\n=============================================\n";
    std::cout << "       영화 추천 시스템: 평균 평점 Top " << N << "      \n";
    std::cout << "=============================================\n";

    // 2. 영화 ID별로 {평점 총점, 평가 참여 횟수}를 누적할 Map 자료구조 생성
    // Key: movieId, Value: pair<평점합, 평가횟수>
    std::map<int, std::pair<double, int>> movieData;

    for (const Rating& r : allRatings) {
        movieData[r.getMovieId()].first += r.getScore();  // 평점 점수 누적 합산
        movieData[r.getMovieId()].second++;               // 해당 영화의 평가 횟수 1 증가
    }

    // 3. 정렬 알고리즘(std::sort)을 쓰기 위해 Map에 있던 데이터를 Vector로 복사
    // 원소 형태: pair<movieId, 계산된_평균평점>
    std::vector<std::pair<int, double>> movieAverages;

    for (const auto& pair : movieData) {
        int movieId = pair.first;
        double totalScore = pair.second.first;
        int count = pair.second.second;
        
        double average = totalScore / count; // 평균 평점 계산
        movieAverages.push_back({movieId, average});
    }

    // 4. 람다 함수를 사용해 평균 평점이 높은 순(내림차순)으로 정렬
    std::sort(movieAverages.begin(), movieAverages.end(),
              [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                  return a.second > b.second; // 앞의 원소 평점이 더 크도록 설정
              });

    // 5. 시스템 내 전체 영화 수가 요구한 N(5개)보다 적을 수 있으므로 std::min으로 제한
    int actualN = std::min(N, static_cast<int>(movieAverages.size()));

    // 6. 최종 결과를 순위별로 콘솔에 출력
    for (int i = 0; i < actualN; ++i) {
        int movieId = movieAverages[i].first;
        double avgScore = movieAverages[i].second;
        int totalVotes = movieData[movieId].second; // 이 영화에 투표한 총 유저 수

        std::cout << "  " << (i + 1) << "위: 영화 ID [" << movieId << "] "
                  << "-> 평균 평점: " << std::fixed << std::setprecision(2) << avgScore << " / 5.0 "
                  << "(" << totalVotes << "명 참여)\n";
    }

    std::cout << "=============================================\n\n";
}