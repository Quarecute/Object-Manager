#include "../include/name_grouping.h"
#include <vector>
#include <algorithm>
#include <map>

std::vector<Group> NameGroupingStrategy::group(const std::vector<WorldObject>& objects) const {
  std::vector<WorldObject> sorted = objects;
  std::sort(sorted.begin(), sorted.end(),
            [](const WorldObject& a, const WorldObject& b) {
              return a.name() < b.name();
            });

  std::map<std::string, std::vector<WorldObject>> groupMap;
  for (const auto& obj : sorted) {
    std::string label = obj.nameGroupLabel();
    groupMap[label].push_back(obj);
  }

  std::vector<Group> result;
  for (auto& [label, vec] : groupMap) {
    if (label != "#") result.push_back({label, std::move(vec)});
  }

  auto it = groupMap.find("#");
  if (it != groupMap.end() && !it->second.empty()) result.push_back({"#", it->second});
  
  return result;
}
