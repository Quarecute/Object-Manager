#include "../../include/commands/group_command.h"
#include "../../include/distance_grouping.h"
#include "../../include/name_grouping.h"
#include "../../include/time_grouping.h"
#include "../../include/type_grouping.h"
#include "../../include/utils.h"

void GroupCommand::execute(AppContext& ctx) {
  ctx.output << "Тип группировки (distance/name/type/time): ";

  std::string type;
  std::getline(ctx.input, type);

  if (type == "distance") {
    DistanceGroupingStrategy strategy;
    printGroups(ctx.output, strategy.group(ctx.objects));
  } else if (type == "name") {
    NameGroupingStrategy strategy;
    printGroups(ctx.output, strategy.group(ctx.objects));
  } else if (type == "time") {
    TimeGroupingStrategy strategy;
    printGroups(ctx.output, strategy.group(ctx.objects));
  } else if (type == "type") {
    ctx.output << "Пороговое значение N: ";

    int threshold;
    ctx.input >> threshold;
    ctx.input.ignore();    

    TypeGroupingStrategy strategy(threshold);
    printGroups(ctx.output, strategy.group(ctx.objects));
  } else {
    ctx.output << "Неизвестный тип группировки\n";
  }
}
