#pragma once

#include "../ICommand.h"

class ListCommand : public ICommand {
  public:
    void execute(AppContext& ctx) override;
};
