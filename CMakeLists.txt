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
        src/zombie.h
        src/zombie.cpp
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