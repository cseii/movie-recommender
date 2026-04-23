#include "UserManager.h"
#include <iostream>

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