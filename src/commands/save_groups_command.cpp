#include <fstream>

#include "../../include/commands/save_groups_command.h"
#include "../../include/distance_grouping.h"
#include "../../include/name_grouping.h"
#include "../../include/time_grouping.h"
#include "../../include/type_grouping.h"
#include "../../include/utils.h"

void SaveGroupsCommand::execute(AppContext& ctx) {
  ctx.output << "Путь для сохранения: ";

  std::string path;
  std::getline(ctx.input, path);

  ctx.output << "Тип группировки (distance/name/type/time): ";
  std::string type;
  std::getline(ctx.input, type);

  std::ofstream file(path);
  if (!file.is_open()) {
    ctx.output << "Не удалось открыть файл\n";
    return;
  }

  if (type == "distance") {
    DistanceGroupingStrategy strategy;
    printGroups(file, strategy.group(ctx.objects));
  } else if (type == "name") {
    NameGroupingStrategy strategy;
    printGroups(file, strategy.group(ctx.objects));
  } else if (type == "time") {
    TimeGroupingStrategy strategy;
    printGroups(file, strategy.group(ctx.objects));
  } else if (type == "type") {
    ctx.output << "Пороговое значение N: ";

    int threshold;
    ctx.input >> threshold;
    ctx.input.ignore();

    TypeGroupingStrategy strategy(threshold);
    printGroups(file, strategy.group(ctx.objects));
  } else {
    ctx.output << "Неизвестный тип группировки\n";
    return;
  }

  ctx.output << "Сохранено в " << path << '\n';
}
