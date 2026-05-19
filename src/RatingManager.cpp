#include "RatingManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

RatingManager::RatingManager() {}

bool RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
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

        std::stringstream ss(line);
        std::string uIdStr, mIdStr, scoreStr;

        if (std::getline(ss, uIdStr, ',')) {
            std::getline(ss, mIdStr, ',');
            std::getline(ss, scoreStr);

            try {
                if (uIdStr.empty() || mIdStr.empty() || scoreStr.empty()) continue;
                int uId = std::stoi(uIdStr);
                int mId = std::stoi(mIdStr);
                double score = std::stod(scoreStr); 
                ratings.push_back(Rating(uId, mId, score));
            } catch (...) {
                continue; 
            }
        }
    }
    file.close();
    return true;
}

bool RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) return false;

    fout << "userId,movieId,score\n";
    for (const Rating& r : ratings) {
        fout << r.getUserId() << "," << r.getMovieId() << "," << r.getScore() << "\n";
    }
    fout.close();
    return true;
}

int RatingManager::size() const {
    return static_cast<int>(ratings.size());
}

std::vector<Rating> RatingManager::findByUser(int userId) const {
    std::vector<Rating> result;
    for (const Rating& r : ratings) {
        if (r.getUserId() == userId) {
            result.push_back(r);
        }
    }
    return result;
}

std::vector<int> RatingManager::getAllUserIds() const {
    std::set<int> idSet;
    for (const Rating& r : ratings) {
        idSet.insert(r.getUserId());
    }
    return std::vector<int>(idSet.begin(), idSet.end());
}

void RatingManager::addRating(const Rating& rating) {
    ratings.push_back(rating);
}