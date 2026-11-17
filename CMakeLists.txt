cmake_minimum_required(VERSION 3.16)
project(LibrarySolid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(library_core
    src/Book.cpp
    src/DatabaseBookRepository.cpp
    src/EmailNotifier.cpp
    src/Library.cpp)
target_include_directories(library_core PUBLIC include)

add_executable(library_app src/main.cpp)
target_link_libraries(library_app PRIVATE library_core)

# GoogleTest: спочатку шукаємо встановлений (наприклад, через vcpkg),
# якщо немає - завантажуємо.
enable_testing()
find_package(GTest CONFIG QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(library_tests tests/library_tests.cpp)
target_link_libraries(library_tests PRIVATE library_core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(library_tests)
