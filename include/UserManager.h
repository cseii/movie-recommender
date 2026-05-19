#pragma once
#include <vector>
#include <string>
#include "user.h"
#include "BaseManager.h"

class UserManager : public BaseManager {
private:
    std::vector<User> users;

public:
    void addUser(const User& user);
    User* findUserById(int id);
    void printAllUsers() const;

    bool loadFromFile(const std::string& filename) override;
    bool saveToFile(const std::string& filename) const override;
    int size() const override;
};