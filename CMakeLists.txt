cmake_minimum_required(VERSION 3.16)
project(Minecraft2D)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES}
        src/main.cpp
        src/map.cpp
        src/map.h
        src/hitbox.cpp
        src/hitbox.h
)

# Указываем путь Homebrew к SFML
set(SFML_ROOT "/opt/homebrew/Cellar/sfml/3.0.2") # поменяй на свою версию
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIB_DIR "${SFML_ROOT}/lib")

# include
include_directories(${SFML_INCLUDE_DIR})

# link
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)
enable_testing()

# ---------- Tests ----------

set(SFML_LIB_DIR "${SFML_ROOT}/lib")

add_executable(game_tests
        tests/update_test.cpp
        tests/death_test.cpp
        tests/spawn_test.cpp
        tests/zombie_test.cpp
        src/zombie.cpp
        src/player.cpp
        src/map.cpp
)

target_link_directories(game_tests PRIVATE ${SFML_LIB_DIR})
target_include_directories(game_tests PRIVATE src)
target_link_libraries(game_tests
        GTest::gtest_main
        sfml-graphics
        sfml-window
        sfml-system
)

include(GoogleTest)
gtest_discover_tests(game_tests
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)