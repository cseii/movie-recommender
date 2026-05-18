#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include <string>

class BaseManager {
public:
    virtual void loadFromFile(
        const std::string& filename
    ) = 0;

    virtual void saveToFile(
        const std::string& filename
    ) const = 0;

    virtual int size() const = 0;

    virtual ~BaseManager() {}
};

#endif