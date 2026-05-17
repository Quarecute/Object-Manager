#include <chrono>

#include "../../include/commands/list_command.h"

void ListCommand::execute(AppContext& ctx) {
  if (ctx.objects.empty()) {
    ctx.output << "Список пуст\n";
    return;
  }

  for (size_t i = 0; i < ctx.objects.size(); ++i) {
    const auto& obj = ctx.objects[i];
    double ts = std::chrono::duration<double>(obj.creationTime().time_since_epoch()).count();

    ctx.output << i << ": " << obj.name()
               << " (" << obj.x() << ", " << obj.y() << ") "
               << obj.type() << " time = " << std::fixed << ts << '\n';
  }
}
