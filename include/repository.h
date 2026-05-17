#pragma once

#include <vector>
#include <string>
#include "object.h"

class ObjectRepository {
  public:
    std::vector<WorldObject> loadFromFile(const std::string& filePath) const;

    void saveToFile(const std::string& filePath, const std::vector<WorldObject>& objects) const;
};
