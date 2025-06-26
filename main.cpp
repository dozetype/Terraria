#include <iostream>
#include <raylib.h>

#include "Game.h"
#include "TextureManager.h"

int main() {
    Game game;
    constexpr int windowWidth {800};
    constexpr int windowHeight {600};
    constexpr Color background {30,30,30,255};
    InitWindow(windowWidth, windowHeight, "hello");
    SetTargetFPS(60);
    TextureManager::loadTextures();


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(background);

        game.update();
        game.draw();
        game.input();
        EndDrawing();
    }


    TextureManager::unloadTextures();
    return 0;
}
