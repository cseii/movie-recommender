#ifndef BASE_MANAGER_H
#define BASE_MANAGER_H

#include <string>

class BaseManager {
public:
    virtual ~BaseManager() {} // 가상 소멸자

    // 순수 가상 함수
    virtual bool loadFromFile(const std::string& filename) = 0;
    virtual bool saveToFile(const std::string& filename) const = 0;
    virtual int size() const = 0;
};

#endif 