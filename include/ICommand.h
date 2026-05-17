#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "object.h"
#include "repository.h"

struct AppContext {
  ObjectRepository& repository;
  std::vector<WorldObject>& objects;
  std::istream& input;
  std::ostream& output;
};

class ICommand {
  public:
    virtual void execute(AppContext& ctx) = 0;
    virtual ~ICommand() = default;
};
