#include "User.h"
#include "Rating.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Movie> movies;

    movies.push_back(Movie(1, "기생충",    "드라마", 2019));
    movies.push_back(Movie(2, "인터스텔라", "SF",    2014));

    movies[0].addRating(4.8);
    movies[1].addRating(4.9);
    movies[1].addRating(6.0);

    std::cout << "\n [Vector 동작 확인] 영화 목록 " << std::endl;
    for (const auto& m : movies) {
        m.display();
    }
    
    std::vector<User> users;
    users.push_back(User(100, "김철수", "kim@ssu.ac.kr"));

    std::vector<Rating> ratings;
    ratings.push_back(Rating(100, 1, 4.5));

    std::cout << "사용자 및 평점 확인" << std::endl;
    users[0].display();
    ratings[0].display();

    return 0;

}