#pragma once

#include "grouping_strategy.h"

class TimeGroupingStrategy : public IGroupingStrategy {
  public:
    std::vector<Group> group(const std::vector<WorldObject>& objects) const override;
};
