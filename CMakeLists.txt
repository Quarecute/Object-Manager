cmake_minimum_required(VERSION 4.3.2)
project(ObjectManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} src/main.cpp
  src/repository.cpp src/distance_grouping.cpp
  src/object.cpp src/name_grouping.cpp
  src/time_grouping.cpp src/type_grouping.cpp
  src/utils.cpp)
