cmake_minimum_required(VERSION 3.7)

project(cpu-usage-tracker C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB_RECURSE MODULES_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/modules/*.c")

include_directories(include)

# Add the library
add_library(${PROJECT_NAME}-modules STATIC ${MODULES_SOURCES})

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} pthread ${PROJECT_NAME}-modules)

enable_testing()

add_subdirectory(tests)
