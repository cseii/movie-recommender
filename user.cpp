#include "user.h"
#include <iostream>
using namespace std;

User::User(int id, const std::string& name,
           const std::string& email)
    : id(id), name(name), email(email) {}

int            User::getId()          const { return id; }
std::string    User::getName()        const { return name; }
std::string    User::getEmail()       const { return email; }

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "User ID: " << user.id << " | Name: " << user.name 
       << " | Email: " << user.email;
    return os;
}

void User::display() const {
    std::cout << *this << std::endl;
}