#include <iostream>
#include <string>
#include <vector>   
#include <fstream>
#include <sstream>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h" 

void showMenu() {
    std::cout << "\n=== Movie Recommender ===" << std::endl;
    std::cout << "[ 영화 ]" << std::endl;
    std::cout << "1. 영화 추가" << std::endl;
    std::cout << "2. 제목으로 검색" << std::endl;
    std::cout << "3. 전체 목록 출력" << std::endl;
    std::cout << "4. 평점순 정렬 출력" << std::endl;
    std::cout << "[ 사용자 ]" << std::endl;
    std::cout << "5. 사용자 추가" << std::endl;
    std::cout << "6. 사용자 목록 출력" << std::endl;
    std::cout << "[ 평점 및 추천 ]" << std::endl; 
    std::cout << "7. 평점 입력" << std::endl;
    std::cout << "8. 영화별 평점 보기" << std::endl;
    std::cout << "9. 맞춤 영화 추천 받기 (M3)" << std::endl; 
    std::cout << "[ 시스템 확장 기능 ]" << std::endl;
    std::cout << "10. 영화별 평균 평점 Top N 통계 보기" << std::endl;
    std::cout << "11. 수동으로 CSV 평점 데이터 백업 실행" << std::endl;
    std::cout << "0. 종료" << std::endl;
    std::cout << "선택> ";
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    // 각각의 csv 파일로부터 기존 백업 데이터를 읽어와 벡터에 적재
    if (!movieMgr.loadFromFile("data/movies.csv")) {
        std::cerr << "[안내] 초기 영화 데이터 파일(data/movies.csv)을 찾을 수 없습니다.\n";
    } else {
        std::cout << "[시스템] 영화 데이터 " << movieMgr.size() << "건을 정상적으로 로드했습니다.\n";
    }

    if (!userMgr.loadFromFile("data/users.csv")) {
        std::cerr << "[안내] 초기 사용자 데이터 파일(data/users.csv)을 찾을 수 없습니다.\n";
    } else {
        std::cout << "[시스템] 사용자 데이터 " << userMgr.size() << "건을 정상적으로 로드했습니다.\n";
    }

    if (!ratingMgr.loadFromFile("data/ratings.csv")) {
        std::cerr << "[안내] 초기 평점 데이터 파일(data/ratings.csv)을 찾을 수 없어 빈 상태로 시작합니다.\n";
    } else {
        std::cout << "[시스템] 평점 데이터 " << ratingMgr.size() << "건을 정상적으로 로드했습니다.\n";
    }

    // 영화별 실시간 평균 평점 계산을 위한 초기 연동 블록
    {
        std::ifstream rFile("data/ratings.csv");
        if (rFile.is_open()) {
            std::string rLine, rHeader;
            if (std::getline(rFile, rHeader)) {}   // 첫 줄 헤더 스킵
            while (std::getline(rFile, rLine)) {
                while (!rLine.empty() && (rLine.back() == '\r' || rLine.back() == '\n')) {
                    rLine.pop_back();
                }
                if (rLine.empty()) continue;
                
                std::stringstream rss(rLine);
                std::string uStr, mStr, sStr;
                if (std::getline(rss, uStr, ',') && std::getline(rss, mStr, ',') && std::getline(rss, sStr)) {
                    try {
                        int mId = std::stoi(mStr);
                        double score = std::stod(sStr);
                        Movie* m = movieMgr.findMovieById(mId);   
                        if (m) {
                            m->addRating(score);   
                        }
                    } catch (...) { continue; }   
                }
            }
            rFile.close();
        }
    }

    // 추천 및 통계 알고리즘 객체 생성
    Recommender recommender(ratingMgr);

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
                
                ratingMgr.addRating(Rating(uId, mId, score));
                
                Movie* m = movieMgr.findMovieById(mId);
                if (m) {
                    m->addRating(score);
                }
                std::cout << "[시스템] 평점이 실시간으로 연동되었습니다.\n";
                break;
            }
            case 8: { 
                std::cout << "=== 영화별 평점 보기 ===\n";
                movieMgr.sortMoviesById();
                movieMgr.printAllMovies();
                break;
            }
            case 9: {   
                int targetUserId, K, N;
                std::cout << "추천을 진행할 대상 사용자 ID: "; std::cin >> targetUserId;
                std::cout << "유사도를 분석할 이웃의 수 (K): "; std::cin >> K;
                std::cout << "추천받을 영화의 최대 개수 (N): "; std::cin >> N;

                std::cout << "\n[알고리즘] User " << targetUserId << " 번의 영화 추천 리스트를 생성하는 중...\n";
                std::vector<int> recommendations = recommender.recommend(targetUserId, K, N);

                if (recommendations.empty()) {
                    std::cout << "=> [안내] 이 사용자에게 추천할 만한 새로운 영화 정보를 찾을 수 없습니다.\n";
                } else {
                    std::cout << "================= [ 맞춤 추천 영화 목록 ] =================\n";
                    for (size_t i = 0; i < recommendations.size(); ++i) {
                        int mId = recommendations[i];
                        std::cout << " " << i + 1 << "위: 영화 ID [ " << mId << " ]";
                        Movie* m = movieMgr.findMovieById(mId);
                        if (m) std::cout << " - 제목: " << m->getTitle();
                        std::cout << "\n";
                    }
                    std::cout << "===========================================================\n";
                }
                break;
            }
            case 10: { 
                recommender.printStatics(); 
                break;
            }
            case 11: {
                std::string backupPath = "data/ratings_backup.csv";
                std::cout << "[시스템] '" << backupPath << "' 경로로 평점 백업을 시도합니다.\n";
                recommender.saveToCSV(backupPath);
                break;
            }
            default:
                std::cout << "잘못된 선택입니다. 다시 입력해 주세요.\n";
        }
    }

    movieMgr.saveToFile("data/movies.csv");
    userMgr.saveToFile("data/users.csv");
    ratingMgr.saveToFile("data/ratings.csv");

    std::cout << "데이터를 파일에 안전하게 저장하고 프로그램을 종료합니다.\n";
    return 0;
}