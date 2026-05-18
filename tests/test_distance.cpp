#include <gtest/gtest.h>
#include "../include/distance_grouping.h"

WorldObject makeObj(const char* name, double x, double y) {
  return WorldObject(name, x, y, "Test", std::chrono::system_clock::now());
}

TEST(DistanceTest, AllGroups) {
  std::vector<WorldObject> objs = {
    makeObj("A", 0, 0),
    makeObj("B", 50, 0),
    makeObj("C", 200, 0),
    makeObj("D", 5000, 0),
    makeObj("E", 20000, 0)
  };
  DistanceGroupingStrategy strategy;
  auto groups = strategy.group(objs);
  ASSERT_EQ(groups.size(), 4);
  EXPECT_EQ(groups[0].name, "До 100 единиц");
  EXPECT_EQ(groups[0].objects.size(), 2);
  EXPECT_EQ(groups[3].name, "Слишком далеко");
  EXPECT_EQ(groups[3].objects.size(), 1);
}
