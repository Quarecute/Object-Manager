#pragma once

#include "grouping_strategy.h"

class TypeGroupingStrategy : public IGroupingStrategy {
  public:
    explicit TypeGroupingStrategy(int threshold);
    std::vector<Group> group(const std::vector<WorldObject>& objects) const override;

  private:
    int threshold_;
};
