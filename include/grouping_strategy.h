#pragma once

#include <vector>
#include <string>
#include "object.h"

struct Group {
  std::string name;
  std::vector<WorldObject> objects;
};

class IGroupingStrategy {
  public:
    virtual std::vector<Group> group(const std::vector<WorldObject>& objects) const = 0;
    virtual ~IGroupingStrategy() = default;
};
