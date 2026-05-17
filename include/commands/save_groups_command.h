#pragma once

#include "../ICommand.h"

class SaveGroupsCommand : public ICommand {
  public:
    void execute(AppContext& ctx) override;
};
