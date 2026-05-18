#ifndef RATING_MANAGER_H
#define RATING_MANAGER_H

#include <vector>
#include <string>
#include "BaseManager.h" 
#include "Rating.h"

class RatingManager : public BaseManager {
private:
    std::vector<Rating> ratings;

public:
    RatingManager();
    virtual ~RatingManager() override {} 

    virtual bool loadFromFile(const std::string& filename) override;
    virtual bool saveToFile(const std::string& filename) const override;
    virtual int size() const override;

    std::vector<Rating> findByUser(int userId) const;
    std::vector<int> getAllUserIds() const;

    void addRating(const Rating& rating);
};

#endif