#include "MovieManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>    // std::sort 알고리즘을 사용하기 위해 포함
#include <iomanip>      // 소수점 출력을 위한 헤더 추가

// 영화 추가 및 정렬
void MovieManager::addMovie(const Movie& movie) {
    movies.push_back(movie);   // 벡터의 맨 뒤에 영화 객체 추가
}

void MovieManager::sortMoviesById() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.getId() < b.getId();
    });
    std::cout << "영화 목록이 ID순으로 정렬되었습니다.\n";
}

void MovieManager::sortMoviesByRating() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.getAverageRating() > b.getAverageRating(); 
    });
    std::cout << "영화 목록이 평점순으로 정렬되었습니다.\n";
}

// 검색 함수 (주소값 반환 및 엣지 케이스 처리)
// Movie* 포인터를 반환하여 원본 배열 내부를 수정할 수 있게 함
Movie* MovieManager::findMovieByTitle(const std::string& title) {
    for (size_t i = 0; i < movies.size(); ++i) {
        if (movies[i].getTitle() == title) {
            return &movies[i];     // 원본 데이터의 주소값 리턴
        }
    }
    return nullptr; 
}

Movie* MovieManager::findMovieById(int id) {
    for (size_t i = 0; i < movies.size(); ++i) {
        if (movies[i].getId() == id) {
            return &movies[i];
        }
    }
    return nullptr;
}

// 연산자 오버로딩 에러를 원천 차단하기 위해 getter 함수들로 직접 분할하여 콘솔에 포맷 출력
void MovieManager::printAllMovies() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    
    for (const auto& movie : movies) {
        std::cout << "ID: " << movie.getId() 
                  << " | 제목: " << movie.getTitle() 
                  << " | 장르: " << movie.getGenre() 
                  << " | 개봉연도: " << movie.getReleaseYear() << "년"
                  << " | ⭐️ 평균 평점: " << std::fixed << std::setprecision(1) << movie.getAverageRating() << " / 5.0\n";
    }
}

int MovieManager::size() const {
    return static_cast<int>(movies.size());
}

// csv 파일 읽기
bool MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;   // 파일이 없거나 열기 실패 시 안전하게 false 반환

    std::string line, header;
    if (std::getline(file, header)) {}   // csv 파일의 첫 줄인 헤더를 읽어서 버림

    // 파일의 끝까지 한 줄씩 읽어옴
    while (std::getline(file, line)) {
        // 컴파일 오류 방지 (\r 개행 문자 제거)
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
            line.pop_back();   // 문자열의 맨 뒤에 숨어있는 줄바꿈 찌꺼기 제거          
        }
        if (line.empty()) continue;   // 빈 줄이면 파싱을 건너뛰고 다음 줄로 진행

        std::stringstream ss(line);
        std::string idStr, title, genre, yearStr;

        // 콤마를 구분자로 삼아 각 필드를 순서대로 분리해냄
        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, title, ',') &&
            std::getline(ss, genre, ',') &&
            std::getline(ss, yearStr)) {
            
            // 엣지 케이스: 데이터 포맷 오염 방어
            try {
                int id = std::stoi(idStr);   // 문자열 숫자를 int로 변환
                int year = std::stoi(yearStr);   // 문자열 개봉 연도를 int로 변환
                movies.push_back(Movie(id, title, genre, year));   // 파싱 완료된 객체를 벡터에 추가
            } catch (...) {
                continue;   // 만약 파일 내에 문자가 섞여 있는 등 stoi 에러가 나면 해당 줄만 패스
            }
        }
    }
    file.close();   // 사용이 끝난 파일 객체 닫기
    return true; 
}

// csv 파일 쓰기
bool MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "id,title,genre,year\n";
    for (const auto& movie : movies) {
        file << movie.getId() << "," 
             << movie.getTitle() << "," 
             << movie.getGenre() << "," 
             << movie.getReleaseYear() << "\n";
    }
    file.close();
    return true;
}