#include <gtest/gtest.h>
#include "../include/type_grouping.h"
#include "object.h"

static WorldObject makeObjType(const std::string& name, const std::string& type) {
  return WorldObject(name, 0., 0., type, std::chrono::system_clock::now());
}

TEST(TypeGroupingTest, ThresholdCreatesGroups) {
  std::vector<WorldObject> objs = {
    makeObjType("A", "дерево"),
    makeObjType("B", "дерево"),
    makeObjType("C", "камень")
  };

  TypeGroupingStrategy strategy(1);
  auto groups = strategy.group(objs);

  ASSERT_EQ(groups.size(), 2u);
  EXPECT_EQ(groups[0].name, "дерево");
  EXPECT_EQ(groups[0].objects.size(), 2u);
  EXPECT_EQ(groups[1].name, "Разное");
  EXPECT_EQ(groups[1].objects.size(), 1u);
}

TEST(TypeGroupingTest, ThresholdZeroAllSeparate) {
  std::vector<WorldObject> objs {
    makeObjType("X", "здание"),
    makeObjType("Y", "машина")
  };

  TypeGroupingStrategy strategy(0);
  auto groups = strategy.group(objs);

  ASSERT_EQ(groups.size(), 2u);
  EXPECT_EQ(groups[0].name, "здание");
  EXPECT_EQ(groups[1].name, "машина");
}

TEST(TypeGroupingTest, AllMisc) {
  std::vector<WorldObject> objs {
    makeObjType("A", "Тип1"),
    makeObjType("B", "Тип2")
  };

  TypeGroupingStrategy strategy(3);
  auto groups = strategy.group(objs);

  ASSERT_EQ(groups.size(), 1u);
  EXPECT_EQ(groups[0].name, "Разное");
  EXPECT_EQ(groups[0].objects.size(), 2u);
}
