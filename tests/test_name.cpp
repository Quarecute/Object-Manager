#include <chrono>
#include <gtest/gtest.h>
#include "../include/name_grouping.h"
#include "object.h"

WorldObject makeObjName(const std::string& name) {
  return WorldObject(name, 0, 0, "T", std::chrono::system_clock::now());
}

TEST(NameGroupingTest, Basic) {
  std::vector<WorldObject> objs = {
    makeObjName("cat"),
    makeObjName("apple"),
    makeObjName("Banana"),
    makeObjName("123"),
    makeObjName("@mail")
  };
  NameGroupingStrategy strategy;
  auto groups = strategy.group(objs);

  ASSERT_EQ(groups.size(), 4);
  EXPECT_EQ(groups[0].name, "A");
  EXPECT_EQ(groups[1].name, "B");
  EXPECT_EQ(groups[2].name, "C");
  EXPECT_EQ(groups[3].name, "#");
  EXPECT_EQ(groups[0].objects.size(), 1);
  EXPECT_EQ(groups[3].objects.size(), 2);
}
