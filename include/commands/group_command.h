#pragma once

#include "../ICommand.h"

class GroupCommand : public ICommand {
  public:
    void execute(AppContext& ctx) override;
};
