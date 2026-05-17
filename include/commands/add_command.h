#pragma once

#include "../ICommand.h"

class AddCommand : public ICommand {
  public:
    void execute(AppContext& ctx) override;
};
