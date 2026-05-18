#include <chrono>
#include <gtest/gtest.h>
#include <ctime>
#include "../include/time_grouping.h"
#include "object.h"

std::chrono::system_clock::time_point makeTime(int year, int mon, int day) {
  std::tm tm {};
  tm.tm_year = year - 1900;
  tm.tm_mon = mon - 1;
  tm.tm_mday = day;
  std::time_t t = std::mktime(&tm);
  return std::chrono::system_clock::from_time_t(t);
}

static WorldObject makeObjTime(const std::string& name, std::chrono::system_clock::time_point tp) {
  return WorldObject(name, 0., 0., "Test", tp);
}

TEST(TimeTest, Categories) {
  auto now = makeTime(2026, 5, 18);

  std::vector<WorldObject> objs {
    makeObjTime("today",     makeTime(2026, 5, 18)),
    makeObjTime("yesterday", makeTime(2026, 5, 17)),
    makeObjTime("week",      makeTime(2026, 5, 13)),
    makeObjTime("month",     makeTime(2026, 5, 01)),
    makeObjTime("year",      makeTime(2026, 1, 10)),
    makeObjTime("earlier",   makeTime(2025, 4, 18)),
  };

  TimeGroupingStrategy strategy;
  auto groups = strategy.group(objs, now);

  ASSERT_EQ(groups.size(), 6u);
  
  EXPECT_EQ(groups[0].name, "Сегодня");
  ASSERT_EQ(groups[0].objects.size(), 1u);
  EXPECT_EQ(groups[0].objects[0].name(), "today");

  EXPECT_EQ(groups[1].name, "Вчера");
  ASSERT_EQ(groups[1].objects.size(), 1u);
  EXPECT_EQ(groups[1].objects[0].name(), "yesterday");

  EXPECT_EQ(groups[2].name, "На этой неделе");
  ASSERT_EQ(groups[2].objects.size(), 1u);
  EXPECT_EQ(groups[2].objects[0].name(), "week");

  EXPECT_EQ(groups[3].name, "В этом месяце");
  ASSERT_EQ(groups[3].objects.size(), 1u);
  EXPECT_EQ(groups[3].objects[0].name(), "month");

  EXPECT_EQ(groups[4].name, "В этом году");
  ASSERT_EQ(groups[4].objects.size(), 1u);
  EXPECT_EQ(groups[4].objects[0].name(), "year");

  EXPECT_EQ(groups[5].name, "Ранее");
  ASSERT_EQ(groups[5].objects.size(), 1u);
  EXPECT_EQ(groups[5].objects[0].name(), "earlier");
}
