#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

void UserManager::addUser(const User& user) {
    if (findUserById(user.getId()) != nullptr) {
        std::cout << "[오류] ID " << user.getId() << " 사용자가 이미 존재합니다.\n";
        return;
    }
    users.push_back(user);
}

User* UserManager::findUserById(int id) {
    for (auto& user : users) {
        if (user.getId() == id) return &user;
    }
    return nullptr;
}

void UserManager::printAllUsers() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다.\n";
        return;
    }
    for (const auto& user : users) {
        user.display();
    }
}

bool UserManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[오류] 유저 파일을 열 수 없습니다: " << filename << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, name;

        if (std::getline(ss, idStr, ',') && std::getline(ss, name)) {
            int id = std::stoi(idStr);

            if (findUserById(id) == nullptr) {
                users.push_back(User(id, name, ""));
            }
        }
    }

    file.close();
    return true;
}

bool UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[오류] 유저 저장을 위한 파일을 생성할 수 없습니다: " << filename << "\n";
        return false;
    }

    for (const auto& user : users) {
        file << user.getId() << "," << user.getName() << "\n";
    }

    file.close();
    return true;
}

int UserManager::size() const {
    return users.size();
}