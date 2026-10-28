cmake_minimum_required(VERSION 3.14)

project(lorelai
  VERSION 1.0.0
  DESCRIPTION "Generate Lorem Ipsum text from C++"
  HOMEPAGE_URL "https://github.com/UltiRequiem/lorem"
  LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Only build the extras when this is the top-level project, not when used through add_subdirectory/FetchContent.
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(LORELAI_IS_TOP_LEVEL ON)
else()
  set(LORELAI_IS_TOP_LEVEL OFF)
endif()

option(LORELAI_BUILD_CLI "Build the lorelai-cli command" ${LORELAI_IS_TOP_LEVEL})
option(LORELAI_BUILD_TESTS "Build the tests" ${LORELAI_IS_TOP_LEVEL})
option(LORELAI_INSTALL "Generate the install target" ${LORELAI_IS_TOP_LEVEL})

add_library(lorelai STATIC src/lorem_ipsum.cpp)
add_library(lorelai::lorelai ALIAS lorelai)

target_include_directories(lorelai PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_features(lorelai PUBLIC cxx_std_17)

if(MSVC)
  set(LORELAI_WARNINGS /W4)
else()
  set(LORELAI_WARNINGS -Wall -Wextra -Wpedantic)
endif()
target_compile_options(lorelai PRIVATE ${LORELAI_WARNINGS})

if(LORELAI_BUILD_CLI)
  add_executable(lorelai-cli src/main.cpp)
  target_link_libraries(lorelai-cli PRIVATE lorelai)
  target_compile_options(lorelai-cli PRIVATE ${LORELAI_WARNINGS})
endif()

if(LORELAI_BUILD_TESTS)
  enable_testing()

  add_executable(test_lorelai tests/lorem_ipsum_test.cpp)
  target_link_libraries(test_lorelai PRIVATE lorelai)
  target_compile_options(test_lorelai PRIVATE ${LORELAI_WARNINGS})
  add_test(NAME LoremIpsumTests COMMAND test_lorelai)

  if(LORELAI_BUILD_CLI)
    add_test(NAME cli_words COMMAND lorelai-cli -w 3)
    set_tests_properties(cli_words PROPERTIES PASS_REGULAR_EXPRESSION "^lorem ipsum dolor[\r\n]+$")

    add_test(NAME cli_paragraphs COMMAND lorelai-cli -p 2 2)
    set_tests_properties(cli_paragraphs PROPERTIES PASS_REGULAR_EXPRESSION "^lorem ipsum[\r\n]+lorem ipsum[\r\n]+$")

    add_test(NAME cli_help COMMAND lorelai-cli --help)
    set_tests_properties(cli_help PROPERTIES PASS_REGULAR_EXPRESSION "Usage: lorelai-cli")

    # Bad input must exit non-zero with a message, never crash.
    foreach(bad "-w abc" "-w -3" "-w 12abc" "-w 99999999999" "-p 1" "--nope")
      string(REPLACE " " "_" name "${bad}")
      separate_arguments(bad_args UNIX_COMMAND "${bad}")
      add_test(NAME cli_rejects_${name} COMMAND lorelai-cli ${bad_args})
      set_tests_properties(cli_rejects_${name} PROPERTIES WILL_FAIL TRUE)
    endforeach()
  endif()
endif()

if(LORELAI_INSTALL)
  include(CMakePackageConfigHelpers)

  install(TARGETS lorelai EXPORT lorelaiTargets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  if(LORELAI_BUILD_CLI)
    install(TARGETS lorelai-cli RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  endif()

  install(EXPORT lorelaiTargets NAMESPACE lorelai:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lorelai)
  configure_package_config_file(cmake/lorelaiConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/lorelaiConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lorelai)
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/lorelaiConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)
  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/lorelaiConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/lorelaiConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lorelai)
endif()
