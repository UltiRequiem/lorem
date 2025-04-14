cmake_minimum_required(VERSION 3.10)

project(cpp-lorelai VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_library(lorelai STATIC src/lorem_ipsum.cpp)

enable_testing()
add_executable(test_lorelai tests/lorem_ipsum_test.cpp)
target_link_libraries(test_lorelai lorelai)
add_test(NAME LoremIpsumTests COMMAND test_lorelai)

add_executable(lorelai-cli src/main.cpp)
target_link_libraries(lorelai-cli lorelai)