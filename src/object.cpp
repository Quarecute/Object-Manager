#include "../include/object.h"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <sstream>
#include <stdexcept>

WorldObject::WorldObject(std::string name, double x, double y,
                         std::string type, std::chrono::system_clock::time_point creationTime)
  : name_(std::move(name))
  , x_(x)
  , y_(y)
  , type_(std::move(type))
  , creationTime_(creationTime)
  {}

const std::string& WorldObject::name() const {
  return name_;
}

double WorldObject::x() const {
  return x_;
}

double WorldObject::y() const {
  return y_;
}

const std::string& WorldObject::type() const {
  return type_;
}

std::chrono::system_clock::time_point WorldObject::creationTime() const {
  return creationTime_;
}

WorldObject WorldObject::fromString(const std::string& line) {
  std::istringstream iss(line);
  std::string name, type;
  double x, y, timestamp;

  if (!(iss >> name >> x >> y >> type >> timestamp)) {
    throw std::runtime_error("Ошибка парсинга строки: " + line);
  }

  std::chrono::system_clock::time_point creationTime(
    std::chrono::duration_cast<std::chrono::system_clock::duration>(
      std::chrono::duration<double>(timestamp)
    )
  );

  return WorldObject(name, x, y, type, creationTime);
}

double WorldObject::distanceFromOrigin() const {
  return std::sqrt(x_ * x_ + y_ * y_);
}

std::string WorldObject::nameGroupLabel() const {
  if (name_.empty()) return "#";

  char first = name_[0];
  if (std::isalpha(static_cast<unsigned char>(first))) {
    return std::string(1, std::toupper(static_cast<unsigned char>(first)));
  }

  return "#";
}

std::string WorldObject::normalizedType() const {
  std::string result = type_;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); } );

  size_t start = result.find_first_not_of(" \t\r\n");
  size_t end = result.find_last_not_of(" \t\r\n");

  if (start == std::string::npos) return result;

  return result.substr(start, end - start + 1);
}
