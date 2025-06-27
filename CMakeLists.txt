cmake_minimum_required(VERSION 3.31)
project(Terraria)

set(CMAKE_CXX_STANDARD 20)

# Homebrew install path on Apple Silicon
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(Terraria src/main.cpp
        src/TextureManager.cpp
        src/TextureManager.h
        src/Player.cpp
        src/Player.h
)


# Link raylib and its dependencies
target_link_libraries(Terraria raylib m pthread dl)
