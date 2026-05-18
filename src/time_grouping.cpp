#include "../include/time_grouping.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <vector>
#include <map>
#include <string>

static struct tm toLocalTm(std::chrono::system_clock::time_point tp) {
  std::time_t t = std::chrono::system_clock::to_time_t(tp);
  struct tm result;
  localtime_r(&t, &result);
  return result;
}

static std::string getTimeCategory(std::chrono::system_clock::time_point objTime, std::chrono::system_clock::time_point now) {
  struct tm objTm = toLocalTm(objTime);
  struct tm nowTm = toLocalTm(now);

  auto sameDay = [](const struct tm& a, const struct tm& b) { return a.tm_year == b.tm_year && a.tm_mon == b.tm_mon && a.tm_mday == b.tm_mday; };

  if (sameDay(objTm, nowTm)) return "Сегодня";

  time_t nowTime = std::chrono::system_clock::to_time_t(now);
  time_t yesterdayTime = nowTime - 86400;

  struct tm yesterdayTm;
  localtime_r(&yesterdayTime, &yesterdayTm);

  if (sameDay(objTm, yesterdayTm)) return "Вчера";

  int daysToMonday = (nowTm.tm_wday == 0) ? 6 : (nowTm.tm_wday - 1);
  time_t mondayTime = nowTime - daysToMonday * 86400;

  struct tm mondayTm;
  localtime_r(&mondayTime, &mondayTm);

  auto dateToInt = [](const struct tm& t) { return (t.tm_year + 1900) * 10000 + (t.tm_mon + 1) * 100 + t.tm_mday; };

  int objDate = dateToInt(objTm);
  int mondayDate = dateToInt(mondayTm);
  int todayDate = dateToInt(nowTm);

  if (objDate >= mondayDate && objDate < todayDate && !sameDay(objTm, yesterdayTm)) return "На этой неделе";
  if (objTm.tm_year == nowTm.tm_year && objTm.tm_mon == nowTm.tm_mon) return "В этом месяце";
  if (objTm.tm_year == nowTm.tm_year) return "В этом году";

  return "Ранее";
}

std::vector<Group> TimeGroupingStrategy::group(const std::vector<WorldObject>& objects, std::chrono::system_clock::time_point now) const {
  std::vector<WorldObject> sorted = objects;
  std::sort(sorted.begin(), sorted.end(),
            [](const WorldObject& a, const WorldObject& b) {
              return a.creationTime() < b.creationTime();
            });

  std::vector<std::string> categories = {
    "Сегодня", "Вчера", "На этой неделе", "В этом месяце", "В этом году", "Ранее"
  };
  std::map<std::string, std::vector<WorldObject>> groupMap;
  
  for (const auto& obj : sorted) {
    std::string cat = getTimeCategory(obj.creationTime(), now);
    groupMap[cat].push_back(obj);
  }

  std::vector<Group> result;
  for (const auto& cat : categories) {
    auto it = groupMap.find(cat);
    if (it != groupMap.end() && !it->second.empty()) result.push_back({cat, it->second});
  }

  return result;
}

std::vector<Group> TimeGroupingStrategy::group(const std::vector<WorldObject>& objects) const {
  return group(objects, std::chrono::system_clock::now());
}
