#pragma once

#include <string>
#include <chrono>

class WorldObject {
  public:
    WorldObject(std::string name, double x, double y,
                std::string type, std::chrono::system_clock::time_point creationTime);

    const std::string& name() const;
    double x() const;
    double y() const;
    const std::string& type() const;
    std::chrono::system_clock::time_point creationTime() const;

    static WorldObject fromString(const std::string& line);

    double distanceFromOrigin() const;
    std::string nameGroupLabel() const;
    std::string normalizedType() const;

  private:
    std::string name_;
    double x_, y_;
    std::string type_;
    std::chrono::system_clock::time_point creationTime_;
};
