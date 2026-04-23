#pragma once
#include <string>
#include <iostream>

class User {
private:
    int         id;
    std::string name;
    std::string email;

public:
    User();
    User(int id, const std::string& name, const std::string& email);

    int         getId()    const;
    std::string getName()  const;
    std::string getEmail() const;

    // [M2 추가] 출력 연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, const User& user);

    void display() const;
};