#include <chrono>
#include <iostream>
#include "../include/grouping_strategy.h"
#include "../include/utils.h"

void printGroups(std::ostream& out, const std::vector<Group>& groups) {
  for (const auto& g : groups) {
    out << '\n' << g.name << '\n';
    for (const auto& obj : g.objects) {
      double timestamp = std::chrono::duration<double>(
        obj.creationTime().time_since_epoch()
      ).count();
      out << obj.name() << ' '
          << obj.x() << ' '
          << obj.y() << ' '
          << obj.type() << ' '
          << std::fixed << timestamp << '\n';
    }
    out << '\n';
  }
}
