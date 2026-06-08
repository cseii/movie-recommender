#include "UserManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

void UserManager::addUser(const User& user) {
    users.push_back(user);
}

void UserManager::printAllUsers() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다.\n";
        return;   // 불필요한 루프를 돌지 않고 즉시 리턴
    }
    for (const auto& user : users) {
        std::cout << "사용자 ID: " << user.getId() 
                  << " | 이름: " << user.getName() 
                  << " | 이메일: " << user.getEmail() << "\n";
    }
}

// 부모 클래스의 순수 가상 함수 size() 실제 구현
int UserManager::size() const {
    return static_cast<int>(users.size());
}

User* UserManager::findUserById(int id) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].getId() == id) {
            return &users[i];
        }
    }
    return nullptr;
}

bool UserManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line, header;
    if (std::getline(file, header)) {} 

    while (std::getline(file, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
            line.pop_back();
        }
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, name, email;

        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, name, ',')) {
            
            if (!std::getline(ss, email)) {
                email = "unknown@example.com";
            }

            try {
                int id = std::stoi(idStr);
                users.push_back(User(id, name, email));
            } catch (...) {
                continue;
            }
        }
    }
    file.close();
    return true;
}

bool UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "id,name,email\n";
    for (const auto& user : users) {
        file << user.getId() << "," 
             << user.getName() << "," 
             << user.getEmail() << "\n";
    }
    file.close();
    return true;
}