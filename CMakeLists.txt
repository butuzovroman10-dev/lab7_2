cmake_minimum_required(VERSION 3.10)
project(BigIntegerMultiplier)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаем директории
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data/test_cases/small)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data/test_cases/medium)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data/test_cases/large)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data/results)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/docs)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/multiplication_algorithms.cpp
    src/test_generator.cpp
    src/performance_tester.cpp
    src/html_reporter.cpp
)

# Исполняемый файл
add_executable(big_int_multiplier ${SOURCES})

# Настройки компиляции
target_compile_features(big_int_multiplier PRIVATE cxx_std_17)
target_include_directories(big_int_multiplier PRIVATE include)

# Флаги компиляции
if(MSVC)
    target_compile_options(big_int_multiplier PRIVATE /W4)
else()
    target_compile_options(big_int_multiplier PRIVATE -Wall -Wextra -O2)
endif()