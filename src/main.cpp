#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "../include/repository.h"
#include "../include/object.h"
#include "../include/distance_grouping.h"
#include "../include/name_grouping.h"
#include "../include/time_grouping.h"
#include "../include/type_grouping.h"
#include "../include/utils.h"

int main() {
    ObjectRepository repo;
    std::vector<WorldObject> objects;

    std::string line;
    while(true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        try {
            if (cmd == "load") {
                std::string path;
                if (!(iss >> path)) { std::cout << "Использование: load <путь>\n"; continue; }
                objects = repo.loadFromFile(path);
                std::cout << "Загружено: " << objects.size() << " объектов\n";
            } else if (cmd == "list") {
                for (size_t i = 0; i < objects.size(); ++i) {
                    const auto& obj = objects[i];
                    std::time_t t = std::chrono::system_clock::to_time_t(obj.creationTime());
                    std::tm* tm = std::localtime(&t);
                    char buf[80];
                    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
                    std::cout << i << ": " << obj.name()
                              << " (" << obj.x() << ", " << obj.y() << ") "
                              << obj.type() << " time = " << buf << '\n';
                }
                if (objects.empty()) std::cout << "Список пуст\n";
            } else if (cmd == "add") {
                std::string name, type;
                double x, y;

                std::cout << "Имя: ";
                std::getline(std::cin, name);

                std::cout << "x: ";
                std::cin >> x;

                std::cout << "y: ";
                std::cin >> y;

                std::cin.ignore();

                std::cout << "Тип: ";
                std::getline(std::cin, type);

                objects.emplace_back(name, x, y, type, std::chrono::system_clock::now());                

                std::cout << "Успешно добавлен!\n";
            } else if (cmd == "save") {
                std::string path;
                if (!(iss >> path)) { std::cout << "Использование: save <путь>\n"; continue; }
                repo.saveToFile(path, objects);
                std::cout << "Сохранено " << objects.size() << " объектов\n";
            } else if (cmd == "group") {
                std::string type;
                if (!(iss >> type)) {
                    std::cout << "Использование: group <тип>\n";
                    std::cout << "Типы: distance\n";
                    continue;
                }
                if (type == "distance") {
                    DistanceGroupingStrategy strategy;
                    auto groups = strategy.group(objects);
                    for (const auto& g : groups) {
                        std::cout << g.name << '\n';
                        for (const auto& obj : g.objects) {
                            std::cout << "  " << obj.name() << " (расстояние: "
                                      << obj.distanceFromOrigin() << ")\n";
                        }
                    }
                } else if (type == "name") {
                    NameGroupingStrategy strategy;
                    auto groups = strategy.group(objects);
                    for (const auto& g : groups) {
                        std::cout << "Группа" << g.name << '\n';
                        for (const auto& obj : g.objects)
                            std::cout << "  " << obj.name() << '\n';
                    }
                } else if (type == "time") {
                    TimeGroupingStrategy strategy;
                    auto groups = strategy.group(objects);
                    for (const auto& g : groups) {
                        std::cout << g.name << '\n';
                        for (const auto& obj : g.objects) {
                            auto ts = std::chrono::duration<double>(obj
                                                                    .creationTime()
                                                                    .time_since_epoch()).count();
                            std::cout << "  " << obj.name() << " (timestamp: " << ts << ")\n";
                        }
                    }
                } else if (type == "type") {
                    int threshold;
                    if (!(iss >> threshold)) {
                        std::cout << "Использование: group type <N>\n";
                        continue;
                    }

                    TypeGroupingStrategy strategy(threshold);
                    auto groups = strategy.group(objects);
                    for (const auto& g : groups) {
                        std::cout << g.name << '\n';
                        for (const auto& obj : g.objects)
                        std::cout << "  " << obj.name() << " (" << obj.type() << ")\n";
                    }
                } else if (cmd == "savegroups") {
                    std::string path, type;
                    if (!(iss >> path >> type)) {
                        std::cout << "Использование: savegroups <путь> <тип> [N]\n"
                                  << "Типы: distance, name, time, type\n";
                        continue;
                    }

                    std::ofstream file(path);
                    if (!file.is_open()) {
                        std::cout << "Не удалось открыть файл для записи: " << path << '\n';
                        continue;
                    }

                    if (type == "distance") {
                        DistanceGroupingStrategy strategy;
                        auto groups = strategy.group(objects);
                        printGroups(file, groups);
                    } else if (type == "name") {
                        NameGroupingStrategy strategy;
                        auto groups = strategy.group(objects);
                        printGroups(file, groups);
                    } else if (type == "time") {
                        int threshold;
                        if (!(iss >> threshold)) {
                            std::cout << "Использование: savegroups <путь> type <N>\n";
                            continue;
                        }
                        TypeGroupingStrategy strategy(threshold);
                        auto groups = strategy.group(objects);
                        printGroups(file, groups);
                    } else {
                        std::cout << "Неизвестный тип группировки: " << type << '\n';
                        continue;
                    }
                    std::cout << "Результаты сохранены в " << path << '\n';
                } else {
                    std::cout << "Неизвестный тип группировки: " << type << '\n';
                }
            } else if (cmd == "exit") {
                break;
            } else {
                std::cout << "Неизестная команда. Доступные команды: load, list, add, save, group, exit\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << '\n';
        }
    }

    return 0;
}
