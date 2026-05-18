#include <gtest/gtest.h>
#include "../include/object.h"
#include <chrono>

TEST(ObjectTest, ParseValid) {
  auto obj = WorldObject::fromString("Кривой -32.23 13.44 Человек 1693235249.98678");
  EXPECT_EQ(obj.name(), "Кривой");
  EXPECT_DOUBLE_EQ(obj.x(), -32.23);
  EXPECT_DOUBLE_EQ(obj.y(), 13.44);
  EXPECT_EQ(obj.type(), "Человек");

  double ts = std::chrono::duration<double>(obj.creationTime().time_since_epoch()).count();
  EXPECT_NEAR(ts, 1693235249.98678, 1e-5);
}

TEST(ObjectTest, ParceIncomplete) {
  EXPECT_THROW(WorldObject::fromString("один"), std::runtime_error);
}
