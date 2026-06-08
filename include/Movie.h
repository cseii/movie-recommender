#pragma once // 중복 포함 방지. 이 파일이 여러번 include되어도 컴파일에러가 나지 않도록함
#include <string>
#include <iostream>

class Movie {
private:
    int         id;
    std::string title;
    std::string genre;
    int         releaseYear;
    double      totalRating;    // 누적 평점을 기록
    int         ratingCount;    // 평점이 몇 개 쌓였는지 개수를 기록

public:
    Movie();                    // 기본 생성자
    Movie(int id, const std::string& title,
          const std::string& genre, int year); //매개변수가 있는 생성자

    // getter 함수들 뒤의 const: 이 함수들은 객체의 멤버 변수를 절대 수정하지 않는 상수 멤버 함수임을 보장
    int         getId()              const;
    std::string getTitle()           const;
    std::string getGenre()           const;
    int         getReleaseYear()     const;  
    double      getAverageRating()   const;  
    int         getRatingCount()     const;  

    void addRating(double r);               // 새로운 평점이 들어왔을 때 totalRating에 r을 더하고, ratingCount를 1 증가

    //연산자 오버로딩
    bool operator==(const Movie& other) const;
    bool operator<(const Movie& other) const;

    //std::cout << movie; 처럼 객체를 바로 출력 스트림에 보낼 수 있게 해줌. private 멤버에 접근하기 위해 friend를 쓴다
    friend std::ostream& operator<<(std::ostream& os, const Movie& movie);

    void display() const;
};