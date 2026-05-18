add_executable(test_runner
  test_object.cpp
  test_distance.cpp
  test_name.cpp
  test_type.cpp
  ${CMAKE_SOURCE_DIR}/src/object.cpp
  ${CMAKE_SOURCE_DIR}/src/distance_grouping.cpp
  ${CMAKE_SOURCE_DIR}/src/name_grouping.cpp
  ${CMAKE_SOURCE_DIR}/src/time_grouping.cpp
  ${CMAKE_SOURCE_DIR}/src/type_grouping.cpp
)

target_include_directories(test_runner PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_runner GTest::gtest_main)
target_compile_features(test_runner PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(test_runner)
