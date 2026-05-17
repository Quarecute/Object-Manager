#include <chrono>
#include <string>

#include "../../include/commands/add_command.h"

void AddCommand::execute(AppContext& ctx) {
  std::string name, type;
  double x, y;

  ctx.output << "Имя: ";
  std::getline(ctx.input, name);

  ctx.output << "x: ";
  ctx.input >> x;

  ctx.output << "y: ";
  ctx.input >> y;

  ctx.input.ignore();

  ctx.output << "Тип: ";
  std::getline(ctx.input, type);

  ctx.objects.emplace_back(name, x, y, type, std::chrono::system_clock::now());

  ctx.output << "Объект добавлен\n";
}
