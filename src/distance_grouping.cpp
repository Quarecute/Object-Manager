#include "../include/distance_grouping.h"
#include <cmath>
#include <algorithm>
#include <vector>

std::vector<Group> DistanceGroupingStrategy::group(const std::vector<WorldObject>& objects) const {
  std::vector<WorldObject> sorted = objects;
  std::sort(sorted.begin(), sorted.end(),
            [](const WorldObject& a, const WorldObject& b) {
              return a.distanceFromOrigin() < b.distanceFromOrigin();
            });

  Group group0_100      { "До 100 единиц",   {} };
  Group group100_1000   { "До 1000 единиц",  {} };
  Group group1000_10000 { "До 10000 единиц", {} };
  Group groupFar        { "Слишком далеко",  {} };

  for (const auto& obj : sorted) {
    double dist = obj.distanceFromOrigin();
    if (dist <= 100.) group0_100.objects.push_back(obj);
    else if (dist <= 1000.) group100_1000.objects.push_back(obj);
    else if (dist <= 10000.) group1000_10000.objects.push_back(obj);
    else groupFar.objects.push_back(obj);
  }

  std::vector<Group> result;
  for (auto& g : { &group0_100, &group100_1000, &group1000_10000, &groupFar }) {
    if (!g->objects.empty()) result.push_back(std::move(*g));
  }

  return result;
}
