#include <iostream>
#include <raylib.h>

#include "Constants.h"
#include "Player.h"
#include "TextureManager.h"

class Tile {
public:
    Tile(Vector2 pos, Texture2D image)
        : pos(pos), image(image) {}
    // ~Block();

    void draw() const {
        DrawTextureV(image, pos, WHITE);
    }

    Texture2D getImage() const {
        return image;
    }

    Rectangle getRec() const {
        return {pos.x, pos.y, TILE_SIZE, TILE_SIZE};
    }

private:
    Vector2 pos;
    Texture2D image;
};

class Dirt:public Tile {
public:
    Dirt(const Vector2 pos, const Texture2D &image)
        :Tile(pos, image){}
    ~Dirt() {
        // std::cout << "removed" <<std::endl;
    }
};

class Game {
public:
    void update() {
        player.setXVel(0);
        player.setYVel(0);
        handleInput();
        // checkForCollisions();
        player.update();
    }

    void draw() {
        player.draw();
        for (auto& block: tiles) {
            block->draw();
        }
    }

    void handleInput() {
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            player.moveLeft();
        }else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            player.moveRight();
        }
    }

    void addBlock(std::shared_ptr<Tile> block) {
        tiles.push_back(block);
    }

    void renderMap() {
        constexpr Vector2 mapSize{MAP_X, MAP_Y};
        const Vector2 startingPt{0,300};
        const Image noiseImg = GenImagePerlinNoise(
            static_cast<int>(mapSize.x),
            static_cast<int>(mapSize.y),
            0, 0, 8.0f);
        Color* pixels = LoadImageColors(noiseImg);

        for (int y=0; y<mapSize.y/TILE_SIZE; y++) {
            for (int x=0; x<mapSize.x/TILE_SIZE; x++) {
                Color color = pixels[y * static_cast<int>(mapSize.x) + x];
                float brightness = color.r / 255.0f;
                Vector2 pos{startingPt.x+x*TILE_SIZE, startingPt.y+y*TILE_SIZE};
                if (brightness < 0.4f || y==0) { addBlock(std::make_shared<Dirt>(pos, TextureManager::getTexture("dirt1"))); }
                else { addBlock(std::make_shared<Dirt>(pos, TextureManager::getTexture("dirt2"))); }
            }
        }
        UnloadImage(noiseImg);
        UnloadImageColors(pixels);
    }

    // void checkForCollisions() {
    //     Rectangle playerRec = player.getRec();
    //
    //     int startX = playerRec.x / TILE_SIZE;
    //     int endX   = (playerRec.x + playerRec.width) / TILE_SIZE;
    //     int startY = playerRec.y / TILE_SIZE;
    //     int endY   = (playerRec.y + playerRec.height) / TILE_SIZE;
    //
    //     for (int y = startY; y <= endY; ++y) {
    //         for (int x = startX; x <= endX; ++x) {
    //             int index = y*TILE_SIZE + x;
    //             if (tiles[index]) { //CHECK IF TILE EXIST
    //                 Rectangle tileRec = tiles[index]->getRec();
    //                 if (CheckCollisionRecs(playerRec, tileRec)) {
    //                     player.
    //                 }
    //             }
    //         }
    //     }

    // }

private:
    Player player;
    std::vector<std::shared_ptr<Tile>> tiles;
};



int main() {
    constexpr int windowWidth {800};
    constexpr int windowHeight {600};
    constexpr Color background {30,30,30,255};

    InitWindow(windowWidth, windowHeight, "hello");
    SetTargetFPS(60);
    Game game;
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;
    TextureManager::loadTexture("dirt1", "images/dirt1.png");
    TextureManager::loadTexture("dirt2", "images/dirt2.png");
    game.renderMap();


    while (!WindowShouldClose()) {
        SetWindowTitle(("FPS: " + std::to_string(GetFPS())).c_str());
        // std::cout << GetFPS() << std::endl;
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(background);

        game.update();
        game.draw();
        EndDrawing();
    }

    TextureManager::unloadAll();
    return 0;
}
