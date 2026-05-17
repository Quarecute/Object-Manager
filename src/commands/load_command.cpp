#include "../../include/commands/load_command.h"
#include <exception>

void LoadCommand::execute(AppContext& ctx) {
  ctx.output << "Введите путь к файлу: ";
  std::string path;
  std::getline(ctx.input, path);
  try {
    ctx.objects = ctx.repository.loadFromFile(path);
    ctx.output << "Загружено " << ctx.objects.size() << " объектов\n";
  } catch (const std::exception& e) {
    ctx.output << "Ошибка: " << e.what() << '\n';
  }
}
