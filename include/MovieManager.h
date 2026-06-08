#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H     // 중복 include 방지

#include <vector>
#include <string>

#include "Movie.h"
#include "BaseManager.h"   // 부모 클래스인 BaseManager 포함

// BaseManager 상속 선언
class MovieManager : public BaseManager {

private:
    // 모든 영화 객체들을 동적 배열 형태로 보관
    std::vector<Movie> movies;

public:
    
    // 영화 추가: 객체 복사 비용을 줄이기 위해 const 참조로 받음
    void addMovie(const Movie& movie);
    
    // ID로 영화 검색: 외부에서 검색된 영화 객체의 내부 값을 수정할 수 있도록함
    Movie* findMovieById(int id);

    // 제목으로 영화 검색
    Movie* findMovieByTitle(
        const std::string& title
    );

    // 모든 영화 출력: 데이터 바꾸지 않는 읽기 전용 함수
    void printAllMovies() const;

    // ID 기준 정렬
    void sortMoviesById();

    // 평점 기준 정렬: 평점이 높은 순
    void sortMoviesByRating();

    // 현재 저장된 영화의 총 개수를 반환하는 getter 함수
    int getMovieCount() const;

    // 부모(BaseManager)의 순수 가상 함수 오버라이딩
    // csv 파일로부터 영화 데이터를 읽어와 movies 벡터에 채워넣는 가상 함수 구현 선언
    bool loadFromFile(const std::string& filename) override;
    
    // movies 벡터에 있는 영화 데이터를 다시 csv 파일로 저장하는 가상 함수 구현 선언
    bool saveToFile(const std::string& filename) const override;

    // 현재 관리 중인 컨테이너의 요소 개수를 반환하는 가상 함수 구현 선언
    int size() const override;
};

#endif