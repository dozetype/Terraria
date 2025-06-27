#include <iostream>
#include <raylib.h>

#include "Player.h"
#include "TextureManager.h"

class Block {
public:
    Block(Vector2 pos, Texture2D image)
        : pos(pos), image(image) {}
    // ~Block();

    void draw() const {
        DrawTextureV(image, pos, WHITE);
    }

    Texture2D getImage() const {
        return image;
    }

private:
    Vector2 pos;
    Texture2D image;
};

class Dirt:public Block {
public:
    Dirt(const Vector2 pos, const Texture2D &image)
        :Block(pos, image){}
    ~Dirt() {
        // std::cout << "removed" <<std::endl;
    }
};

class Game {
public:
    void update() {
        handleInput();
        // player.externalForce({0, gravity});
    }

    void draw() {
        player.draw();
        for (auto& block: blocks) {
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

    void addBlock(std::shared_ptr<Block> block) {
        blocks.push_back(block);
    }

    void renderMap() {
        const int width = 8;
        const Vector2 startingPt{0,300};
        const Vector2 mapSize{100, 40};
        Image noiseImg = GenImagePerlinNoise(
            static_cast<int>(mapSize.x),
            static_cast<int>(mapSize.y),
            0, 0, 1.0f);
        Color* pixels = LoadImageColors(noiseImg);

        for (int y=0; y<mapSize.y; y++) {
            for (int x=0; x<mapSize.x; x++) {
                Color color = pixels[y * static_cast<int>(mapSize.x) + x];
                float brightness = color.r / 255.0f;
                Vector2 pos{startingPt.x+x*width, startingPt.y+y*width};
                if (brightness < 0.4f || y==0) { addBlock(std::make_shared<Dirt>(pos, TextureManager::getTexture("dirt1"))); }
                else { addBlock(std::make_shared<Dirt>(pos, TextureManager::getTexture("dirt2"))); }
            }
        }
        UnloadImage(noiseImg);
        UnloadImageColors(pixels);
    }

private:
    float gravity = 1;
    Player player;
    std::vector<std::shared_ptr<Block>> blocks;
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
