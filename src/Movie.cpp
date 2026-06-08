#include "Movie.h"
#include <iostream>

// 기본 생성자
Movie::Movie()
    : id(0), releaseYear(0),
      totalRating(0.0), ratingCount(0) {}   // 생성자 초기화 리스트

// 4인자 생성자
// 외부에서 데이터 받아 실제 영화 객체 생성, 원본 보호
Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)
    : id(id), title(title), genre(genre),        // 입력받은 매개변수 값으로 멤버 변수들 즉시 초기화
      releaseYear(year),
      totalRating(0.0), ratingCount(0) {}        

// getter 함수들
// 내부 데이터 변경불가
int         Movie::getId()           const { return id; }
std::string Movie::getTitle()        const { return title; }
std::string Movie::getGenre()        const { return genre; }
int         Movie::getReleaseYear()  const { return releaseYear; }
int         Movie::getRatingCount()  const { return ratingCount; }

// 평균 평점 계산 함수
double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;   // 엣지 케이스: 0 나눗셈 방어
    return totalRating / ratingCount;   // 평점이 존재할 때만 평균 계산
}

// 평점 추가 함수
void Movie::addRating(double r) {
    if (r < 0.0 || r > 5.0) return;    // 엣지 케이스: 유효성 검사
    totalRating += r;                  // 정상적인 점수일때만 합산
    ratingCount++;                     // 평점 개수 1 증가
}

//연산자 오버로딩
bool Movie::operator==(const Movie& other) const {
    return this->id == other.id;
};

bool Movie::operator<(const Movie& other) const {
    return this->id < other.id;
}

//출력 연산자
//Movie::가 붙지 않은 전역 함수
std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    os << "[" << movie.id << "] " << movie.title 
       << " (" << movie.releaseYear << ") | 장르: " << movie.genre 
       << " | 평점: " << movie.getAverageRating()
       << " (" << movie.ratingCount << "건)";
    return os;
}

// 자체 출력 함수
void Movie::display() const {
    std::cout << *this << std::endl;
}