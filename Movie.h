#pragma once
#include <string>
#include <iostream>

class Movie {
private:
    int         id;
    std::string title;
    std::string genre;
    int         releaseYear;
    double      totalRating;    // averageRating 제거
    int         ratingCount;    // 추가

public:
    Movie();                    // 기본 생성자 추가
    Movie(int id, const std::string& title,
          const std::string& genre, int year);

    int         getId()              const;
    std::string getTitle()           const;
    std::string getGenre()           const;
    int         getReleaseYear()     const;  // getYear → getReleaseYear
    double      getAverageRating()   const;  // getRating → getAverageRating
    int         getRatingCount()     const;  // 추가

    void addRating(double r);               // 추가

    //M2 핵심 추가
    bool operator==(const Movie& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Movie& movie);

    void display() const;
};
