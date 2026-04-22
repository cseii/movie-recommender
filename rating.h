#pragma once
#include <iostream>

class Rating {
private:
    int    userId;
    int    movieId;
    double score;

public:
    Rating();
    Rating(int uId, int mId, double s);

    int    getUserId()  const;
    int    getMovieId() const;
    double getScore()   const;

    // [M2 추가] 출력 연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, const Rating& rating);

    void display() const;
};