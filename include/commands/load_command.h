#pragma once

#include "../ICommand.h"

class LoadCommand : public ICommand {
  public:
    void execute(AppContext& ctx) override;
};
