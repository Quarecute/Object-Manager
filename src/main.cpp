#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <memory>

#include "../include/ICommand.h"
#include "../include/commands/load_command.h"
#include "../include/commands/list_command.h"
#include "../include/commands/add_command.h"
#include "../include/commands/group_command.h"
#include "../include/commands/save_groups_command.h"
#include "../include/repository.h"
#include "../include/object.h"

int main() {
    ObjectRepository repo;
    std::vector<WorldObject> objects;

    AppContext ctx{ repo, objects, std::cin, std::cout };

    std::map<int, std::unique_ptr<ICommand>> menu;
    menu[1] = std::make_unique<LoadCommand>();
    menu[2] = std::make_unique<ListCommand>();
    menu[3] = std::make_unique<AddCommand>();
    menu[4] = std::make_unique<GroupCommand>();
    menu[5] = std::make_unique<SaveGroupsCommand>();

    while (true) {
        std::cout << "\033[2J\033[H";
        std::cout << "\n               [ МЕНЮ ]                \n"
                  << "1. Загрузить объекты из файла            \n"
                  << "2. Показать спиcок объектов              \n"
                  << "3. Добавить объект                       \n"
                  << "4. Группировать и вывести на экран       \n"
                  << "5. Сохранить результат группировки в файл\n"
                  << "6. Выход                                 \n"
                  << "\nВыберите действие: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 6) {
            std::cout << "До свидания!\n";
            break;
        }

        auto it = menu.find(choice);
        if (it != menu.end()) {
            it->second->execute(ctx);
        } else {
            std::cout << "Неверный пункт. Попробуйте снова.\n";
        }

        system("read");
    }
    
    return 0;
}
