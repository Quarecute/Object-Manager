#include <algorithm>
#include <map>
#include <vector>
#include "../include/type_grouping.h"

TypeGroupingStrategy::TypeGroupingStrategy(int threshold)
  : threshold_(threshold) {}

std::vector<Group> TypeGroupingStrategy::group(const std::vector<WorldObject>& objects) const {
  std::map<std::string, int> typeCount;

  for (const auto& obj : objects) {
    typeCount[obj.normalizedType()]++;
  }

  std::map<std::string, bool> passesThreshold;
  for (const auto& [type, count] : typeCount) {
    passesThreshold[type] = (count > threshold_);
  }

  std::map<std::string, std::vector<WorldObject>> groupMap;
  for (const auto& obj : objects) {
    std::string normType = obj.normalizedType();
    if (passesThreshold[normType]) groupMap[normType].push_back(obj);
    else groupMap["Разное"].push_back(obj);
  }

  for (auto& [name, vec] : groupMap) {
    std::sort(vec.begin(), vec.end(),
              [](const WorldObject& a, const WorldObject& b) {
                return a.name() < b.name();
              });
  }

  std::vector<Group> result;
  std::vector<std::string> sortedTypes;

  for (const auto& [type, _] : groupMap) if (type != "Разное") sortedTypes.push_back(type);

  std::sort(sortedTypes.begin(), sortedTypes.end());
  for (const auto& type : sortedTypes) result.push_back({type, groupMap[type]});

  auto itMisc = groupMap.find("Разное");
  if (itMisc != groupMap.end() && !itMisc->second.empty()) result.push_back({"Разное", itMisc->second});

  return result;
}
