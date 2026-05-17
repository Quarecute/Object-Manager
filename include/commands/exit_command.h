#pragma once

#include "../ICommand.h"

class ExitCommand : public ICommand {
  public:
    void execute(AppContext& ctx) override {
      ctx.output << "Выход\n";
    }
};
