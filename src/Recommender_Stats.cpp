#include "Recommender.h"
#include <map>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

// 추가 기능: 영화별 평균 평점 Top N 산출 및 출력 함수
void Recommender::printStatics() const {
    std::vector<int> allUserIds = ratingManager.getAllUserIds();
    
    if (allUserIds.empty()) {
        std::cout << "\n[Notice] 분석할 평점 데이터가 메모리에 존재하지 않습니다.\n";
        return;
    }

    int n = 5; 

    std::map<int, std::pair<double, int>> movieData;
    for (int userId : allUserIds) {
        std::vector<Rating> userRatings = ratingManager.findByUser(userId);
        for (const Rating& r : userRatings) {
            movieData[r.getMovieId()].first += r.getScore();
            movieData[r.getMovieId()].second++;
        }
    }

    if (movieData.empty()) {
        std::cout << "\n[Notice] 분석할 평점 데이터가 메모리에 존재하지 않습니다.\n";
        return;
    }

    std::vector<std::pair<int, double>> movieAverages;
    for (const auto& pair : movieData) {
        movieAverages.push_back({pair.first, pair.second.first / pair.second.second});
    }

    auto sorted = movieAverages;
    std::sort(sorted.begin(), sorted.end(),
              [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                  return a.second > b.second;
              });

    if (n > static_cast<int>(sorted.size())) {
        n = sorted.size();
    }

    std::vector<std::pair<int, double>> topN(sorted.begin(), sorted.begin() + n);

    std::cout << "\n=============================================\n";
    std::cout << "      영화 추천 시스템: 평균 평점 Top " << n << "      \n";
    std::cout << "=============================================\n";

    for (int i = 0; i < n; ++i) {
        int movieId = topN[i].first;
        double avgScore = topN[i].second;
        int totalVotes = movieData[movieId].second;

        std::cout << "  " << (i + 1) << "위: 영화 ID [" << movieId << "] "
                  << "-> 평균 평점: " << std::fixed << std::setprecision(2) << avgScore << " / 5.0 "
                  << "(" << totalVotes << "명 참여)\n";
    }
    std::cout << "=============================================\n\n";
}

// 추가 기능: 추천 결과를 CSV 파일로 내보내는 함수
bool Recommender::saveToCSV(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "[Error] 파일을 생성하거나 열 수 없습니다: " << filename << "\n";
        return false; // 실패 시 false 반환
    }

    fout << "Rank,MovieID,AverageRating\n";

    std::vector<int> allUserIds = ratingManager.getAllUserIds();
    std::map<int, std::pair<double, int>> movieData;
    
    for (int userId : allUserIds) {
        std::vector<Rating> userRatings = ratingManager.findByUser(userId);
        for (const Rating& r : userRatings) {
            movieData[r.getMovieId()].first += r.getScore();
            movieData[r.getMovieId()].second++;
        }
    }

    std::vector<std::pair<int, double>> movieAverages;
    for (const auto& pair : movieData) {
        movieAverages.push_back({pair.first, pair.second.first / pair.second.second});
    }

    std::sort(movieAverages.begin(), movieAverages.end(),
              [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                  return a.second > b.second;
              });

    fout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < movieAverages.size(); ++i) {
        fout << (i + 1) << "," << movieAverages[i].first << "," << movieAverages[i].second << "\n";
    }

    fout.close();
    std::cout << "[System] 성공적으로 통계 데이터를 " << filename << "에 내보냈습니다!\n";
    return true; // 성공 시 true 반환
}