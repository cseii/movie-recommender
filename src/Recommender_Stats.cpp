#include "Recommender.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>

// 추가 기능: 영화별 평균 평점 Top N 산출 및 출력 함수
void Recommender::printStatics() const { 
    // 1. 전체 평점 데이터 가져오기
    const std::vector<Rating>& allRatings = ratingManager.getRatings();
    
    if (allRatings.empty()) {
        std::cout << "\n[Notice] 분석할 평점 데이터가 메모리에 존재하지 않습니다.\n";
        return;
    }

    // 추출하고 싶은 상위 개수 지정 (Top 5)
    int n = 5; 

    // 2. 영화 ID별로 {평점 총점, 평가 횟수}를 누적할 맵 생성
    std::map<int, std::pair<double, int>> movieData;
    for (const Rating& r : allRatings) {
        movieData[r.getMovieId()].first += r.getScore();
        movieData[r.getMovieId()].second++;
    }

    // 3. {영화ID, 평균평점} 쌍을 저장할 벡터 생성 및 데이터 산출
    std::vector<std::pair<int, double>> movieAverages;
    for (const auto& pair : movieData) {
        movieAverages.push_back({pair.first, pair.second.first / pair.second.second});
    }

    auto sorted = movieAverages;  // 복사 (원본 보호)

    // PPT 람다식 정렬 그대로 적용 (내림차순 정렬)
    std::sort(sorted.begin(), sorted.end(),
              [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                  return a.second > b.second; // 내림차순
              });

    // PPT의 static_cast를 이용한 바운더리 방어 코드 그대로 적용
    if (n > static_cast<int>(sorted.size())) {
        n = sorted.size();
    }

    // PPT의 자르기(슬라이싱) 메커니즘을 이용해 상위 n개만 분리 추출
    std::vector<std::pair<int, double>> topN(sorted.begin(), sorted.begin() + n);

    // 4. 최종 결과 출력 화면 구성
    std::cout << "\n=============================================\n";
    std::cout << "      영화 추천 시스템: 평균 평점 Top " << n << "      \n";
    std::cout << "=============================================\n";

    for (int i = 0; i < n; ++i) {
        int movieId = topN[i].first;
        double avgScore = topN[i].second;
        int totalVotes = movieData[movieId].second; // 맵에서 투표 참여 인원 가져오기

        std::cout << "  " << (i + 1) << "위: 영화 ID [" << movieId << "] "
                  << "-> 평균 평점: " << std::fixed << std::setprecision(2) << avgScore << " / 5.0 "
                  << "(" << totalVotes << "명 참여)\n";
    }

    std::cout << "=============================================\n\n";
}