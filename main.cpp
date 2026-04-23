#include <iostream>
#include <string>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"

void showMenu() {
    std::cout << "\n=== Movie Recommender ===" << std::endl;
    std::cout << "[ 영화]" << std::endl;
    std::cout << "1. 영화추가" << std::endl;
    std::cout << "2. 제목으로검색" << std::endl;
    std::cout << "3. 전체목록출력" << std::endl;
    std::cout << "4. 평점순정렬출력" << std::endl;
    std::cout << "[ 사용자]" << std::endl;
    std::cout << "5. 사용자추가" << std::endl;
    std::cout << "6. 사용자목록출력" << std::endl;
    std::cout << "[ 평점]" << std::endl;
    std::cout << "7. 평점입력" << std::endl;
    std::cout << "8. 영화별평점보기" << std::endl;
    std::cout << "0. 종료" << std::endl;
    std::cout << "선택> ";
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    int choice;
    while (true) {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                int id, year; std::string title, genre;
                std::cout << "영화 ID: "; std::cin >> id; std::cin.ignore();
                std::cout << "제목: "; std::getline(std::cin, title);
                std::cout << "장르: "; std::getline(std::cin, genre);
                std::cout << "개봉연도: "; std::cin >> year;
                movieMgr.addMovie(Movie(id, title, genre, year));
                break;
            }
            case 2: {
                std::string title;
                std::cout << "검색할 제목: "; std::cin.ignore(); std::getline(std::cin, title);
                Movie* m = movieMgr.findMovieByTitle(title);
                if (m) std::cout << "찾은 영화: " << *m << std::endl;
                else std::cout << "해당 제목의 영화가 없습니다.\n";
                break;
            }
            case 3:
                movieMgr.sortMoviesById();
                movieMgr.printAllMovies();
                break;
            case 4:
                movieMgr.sortMoviesByRating();
                movieMgr.printAllMovies();
                break;
            case 5: {
                int id; std::string name, email;
                std::cout << "사용자 ID: "; std::cin >> id; std::cin.ignore();
                std::cout << "이름: "; std::getline(std::cin, name);
                std::cout << "이메일: "; std::getline(std::cin, email);
                userMgr.addUser(User(id, name, email));
                break;
            }
            case 6: 
                userMgr.printAllUsers();
                break;
            case 7: {
                int uId, mId; double score;
                std::cout << "사용자 ID: "; std::cin >> uId;
                std::cout << "영화 ID: "; std::cin >> mId;
                std::cout << "평점 (0.0~5.0): "; std::cin >> score;
                ratingMgr.addRating(Rating(uId, mId, score), movieMgr);
                break;
            }
            case 8: { 
                movieMgr.printAllMovies(); 
                break;
            }
            default:
                std::cout << "잘못된 선택입니다.\n";
        }
    }
    std::cout << "프로그램을 종료합니다.\n";
    return 0;
}