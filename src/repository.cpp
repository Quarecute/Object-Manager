#include "../include/repository.h"
#include <chrono>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>

std::vector<WorldObject> ObjectRepository::loadFromFile(const std::string& filePath) const {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл: " + filePath);
  }

  std::vector<WorldObject> objects;
  std::string line;
  int lineNumber = 0;

  while (std::getline(file, line)) {
    ++lineNumber;
    if (line.empty()) continue;

    try {
      objects.push_back(WorldObject::fromString(line));
    } catch (const std::exception& e) {
      std::ostringstream oss;
      oss << "Ошибка в строке: " << lineNumber << ": " << e.what();
      throw std::runtime_error(oss.str());
    }
  }

  return objects;
}

void ObjectRepository::saveToFile(const std::string& filePath, const std::vector<WorldObject>& objects) const {
  std::ofstream file(filePath);
  if (!file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл для записи: " + filePath);
  }

  for (const auto& obj : objects) {
    auto duration = obj.creationTime().time_since_epoch();
    double timestamp = std::chrono::duration<double>(duration).count();

    file << obj.name() << ' '
         << obj.x()    << ' '
         << obj.y()    << ' '
         << obj.type() << ' '
         << std::fixed << timestamp << '\n';
  }
}
