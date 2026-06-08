#include "RatingManager.h"
#include <fstream>   // 파일 입출력 스트림
#include <sstream>   // 문자열을 콤마 단위로 파싱하기 위함
#include <iostream>  // 표준 입출력을 위함
#include <set>       // 중복을 자동으로 제거해 주는 STL std::set을 쓰기 위함
#include <iomanip>  

RatingManager::RatingManager() {}

bool RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);   // 파일 읽기 스트림 오픈
    if (!file.is_open()) {
        return false;
    }

    std::string line, header;
    if (std::getline(file, header)) { /* 헤더 패스 */ }

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) continue;

        std::stringstream ss(line);   // 한 줄의 문자열을 파싱하기 위해 스트림 객체로 변환
        std::string uIdStr, mIdStr, scoreStr;

        if (std::getline(ss, uIdStr, ',')) {
            std::getline(ss, mIdStr, ',');
            std::getline(ss, scoreStr);

            try {
                if (uIdStr.empty() || mIdStr.empty() || scoreStr.empty()) continue;
                int uId = std::stoi(uIdStr);
                int mId = std::stoi(mIdStr);
                double score = std::stod(scoreStr);   // 평점 점수 실수 변환
                ratings.push_back(Rating(uId, mId, score));
            } catch (...) {
                continue;   // 파일 내부 자료형이 잘못되어 에러가 나면 해당 줄만 버리고 계속 진행
            }
        }
    }
    file.close();   // 파일 스트림 명시적 닫기
    return true;
}

bool RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream fout(filename);   // 파일 쓰기 스트림 오픈
    if (!fout.is_open()) return false;

    fout << "userId,movieId,score\n";   // csv 포맷 헤더 쓰기
    
    // 평점이 소수점 첫째 자리나 둘째 자리까지 예쁘게 저장되도록 스트림 포맷 설정
    fout << std::fixed << std::setprecision(1); 

    for (const Rating& r : ratings) {
        // 콤마로 결합하여 텍스트로 밀어 넣음
        fout << r.getUserId() << "," << r.getMovieId() << "," << r.getScore() << "\n";
    }
    fout.close();   // 파일 스트림 닫기
    return true;
}

// 부모 가상 함수 구현: 현재 저장된 평점 데이터의 전체 건수 반환
int RatingManager::size() const {
    // ratings.size()는 size_t(부호 없는 정수)를 반환하므로, 안전하게 int로 static_cast 형변환하여 리턴
    return static_cast<int>(ratings.size());
}

// 특정 유저가 남긴 평점 목록만 필터링하여 따로 벡터로 모아 반환하는 함수
std::vector<Rating> RatingManager::findByUser(int userId) const {
    std::vector<Rating> result;
    for (const Rating& r : ratings) {
        if (r.getUserId() == userId) {
            result.push_back(r);
        }
    }
    return result;
}

// 시스템에 존재하는 모든 고유 유저 ID 리스트 뽑아내기
std::vector<int> RatingManager::getAllUserIds() const {
    std::set<int> idSet;   // 정렬과 중복 제거를 자동으로 해주는 이진 탐색 트리 컨테이너 선언
    for (const Rating& r : ratings) {
        idSet.insert(r.getUserId());   // 한 유저가 여러 평점을 남겼어도 set의 특성상 중복 없이 단 한번만 저장
    }
    // 중복이 제거된 set의 시작과 끝 범위를 이용해 최종 결과물인 vector<int>로 한 번에 변환하여 리턴
    return std::vector<int>(idSet.begin(), idSet.end());
}

// 실시간 평점 추가 함수
void RatingManager::addRating(const Rating& rating) {
    ratings.push_back(rating);
}