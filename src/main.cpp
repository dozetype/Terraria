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
        int width = 8;
        for (float i=0; i<GetScreenWidth()/width; i++) {
            for (float j=0; j<GetScreenHeight()/2/width; j++) {
                addBlock(std::make_shared<Dirt>(Vector2{i*width, j*width}, TextureManager::getTexture("dirt1")));
            }
        }
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
    camera.zoom = 2.0f;
    TextureManager::loadTexture("dirt1", "images/dirt1.png");
    TextureManager::loadTexture("dirt2", "images/dirt2.png");
    // game.addBlock(std::make_shared<Dirt>(Vector2{158, 300}, TextureManager::getTexture("dirt1"))); //?
    // game.addBlock(std::make_shared<Dirt>(Vector2{140, 300}, TextureManager::getTexture("dirt1")));
    // game.addBlock(std::make_shared<Dirt>(Vector2{170, 300}, TextureManager::getTexture("dirt1")));
    game.renderMap();


    while (!WindowShouldClose()) {
        SetWindowTitle(("FPS: " + std::to_string(GetFPS())).c_str());
        // std::cout << GetFPS() << std::endl;
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(background);
        DrawTexture(TextureManager::getTexture("dirt2"), 100, 200, WHITE);

        game.update();
        game.draw();
        EndDrawing();
    }

    TextureManager::unloadAll();
    return 0;
}
