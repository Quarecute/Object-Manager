#pragma once

#include "grouping_strategy.h"

class TimeGroupingStrategy : public IGroupingStrategy {
  public:
    std::vector<Group> group(const std::vector<WorldObject>& objects) const override;
    std::vector<Group> group(const std::vector<WorldObject>& objects, std::chrono::system_clock::time_point now) const;
};
