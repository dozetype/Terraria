#include <iostream>
#include <raylib.h>

#include "Constants.h"
#include "Player.h"
#include "TextureManager.h"

class Tile {
public:
    Tile(const Vector2 pos, const Texture2D &image)
        : pos(pos), image(image) {}
    // ~Block();

    void draw() const { DrawTextureV(image, pos, WHITE); }
    Texture2D getImage() const { return image; }
    Rectangle getRec() const { return {pos.x, pos.y, TILE_SIZE, TILE_SIZE}; }
    int getX() const {return pos.x; }
    int getY() const { return pos.y; }

private:
    Vector2 pos;
    Texture2D image;
};

class Dirt:public Tile {
public:
    Dirt(const Vector2 pos, const Texture2D &image)
        :Tile(pos, image){}
    // ~Dirt() {}
};

class Game {
public:
    void update() {
        player.setXVel(0);
        player.setYVel(GRAVITY);

        handleInput();
        checkForCollisions();
        player.update();
    }

    void draw(const float zoom) const {
        player.draw();

        Vector2 playerPos = player.getPos();
        const int startY = (playerPos.y-GetScreenHeight()/zoom/2) / TILE_SIZE;
        const int endY = (playerPos.y+GetScreenHeight()/zoom/2) / TILE_SIZE;
        const int startX = (playerPos.x-GetScreenWidth()/zoom/2) / TILE_SIZE;
        const int endX = (playerPos.x+GetScreenWidth()/zoom/2) / TILE_SIZE;
        int counter{};
        for (int y=startY; y<=endY; y++) {
            for (int x=startX; x<=endX; x++) {
                auto& tile = tiles[y*(MAP_X/TILE_SIZE) + x];
                if (tile) {
                    tile->draw();
                    counter++;
                }
            }
        }

    }

    void handleInput() {
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) { player.moveLeft(); }
        else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { player.moveRight(); }

        if (player.getGrounded() && IsKeyPressed(KEY_SPACE)) {
            player.moveJump();
            player.setGrounded(false);
        }
    }

    void addBlock(const std::shared_ptr<Tile> &block) {
        tiles.push_back(block);
    }

    void renderMap() {
        constexpr int columns = MAP_X / TILE_SIZE;
        constexpr int rows = MAP_Y / TILE_SIZE;
        std::vector<int> heightMap(columns);
        // NOISE1: MAP NOISE
        const Image noiseImg = GenImagePerlinNoise(MAP_X, MAP_Y, 0, 0, 9.0f);
        Color* pixels = LoadImageColors(noiseImg);
        // NOISE2: HEIGHT NOISE
        const Image noiseImg2 = GenImagePerlinNoise(MAP_X, MAP_Y, 0, 0, 8.f); //INCREASE FOR SPARSITY
        Color* pixels2 = LoadImageColors(noiseImg2);

        for (int x = 0; x < columns; x++) {
            heightMap[x] = pixels2[x].r/3 + 10;
        }

        int counter{};
        for (int y=0; y<rows; y++) {
            for (int x=0; x<columns; x++) {
                if (y >= heightMap[x]) {
                    Color colour = pixels[y * static_cast<int>(MAP_X) + x];
                    float brightness = colour.r; //0-255
                    Vector2 pos{static_cast<float>(x*TILE_SIZE), static_cast<float>(y*TILE_SIZE)};
                    if (y==heightMap[x]) { addBlock(std::make_shared<Dirt>(pos, TextureManager::getTexture("dirt1"))); }
                    else if (brightness < 60){ addBlock(std::make_shared<Dirt>(pos, TextureManager::getTexture("stone"))); }
                    else if (brightness < 255){ addBlock(std::make_shared<Dirt>(pos, TextureManager::getTexture("dirt2"))); }
                }
                else {
                    addBlock(nullptr);
                    counter++;
                }
            }
        }
        std::cout<<"TOTAL TILES: "<<tiles.size()<<"\n"<<"EMPTY SPACE: "<<counter<<std::endl;
        UnloadImage(noiseImg);
        UnloadImageColors(pixels);
        UnloadImage(noiseImg2);
        UnloadImageColors(pixels2);
    }

    Player& getPlayer() {
        return player;
    }

    void checkForCollisions() {
        Rectangle playerRec = player.getRec();

        const int startX = playerRec.x;
        const int endX   = playerRec.x + playerRec.width;
        const int startY = playerRec.y;
        const int endY   = playerRec.y + playerRec.height;

        int radius = 16;

        for (int y=startY-radius; y<=endY+radius; y+=8) {
            for (int x=startX-radius; x<=endX+radius; x+=8) {
                if (x<0 || y<0 || x>=MAP_X || y>=MAP_Y) continue;
                int dx = x - startX;
                int dy = y - startY;
                if (dx*dx + dy*dy > radius*radius){ continue; } // outside

                const int tileX = x / TILE_SIZE;
                const int tileY = y / TILE_SIZE;
                const int index = tileY * (MAP_X / TILE_SIZE) + tileX;
                auto& tile = tiles[index];
                if (tile && CheckCollisionRecs(playerRec, tile->getRec())) {
                    float dx = (playerRec.x + playerRec.width / 2) - (tile->getX() + 8 / 2);
                    float dy = (playerRec.y + playerRec.height / 2) - (tile->getY() + 8 / 2);
                    float overlapX = (playerRec.width / 2 + 8 / 2) - std::abs(dx);
                    float overlapY = (playerRec.height / 2 + 8 / 2) - std::abs(dy);

                    int num{};
                    if (overlapX < overlapY) {
                        num = (dx < 0) ? -overlapX : overlapX;
                        num += playerRec.x;
                        player.setXPos(num);
                    } else {
                        player.setGrounded(true);
                        num = (dy < 0) ? -overlapY : overlapY;
                        num += playerRec.y;
                        player.setYPos(num);
                    }
                }
                // DrawRectangle(x+5, y+5, 3, 3, RED);
            }
        }
    }

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
    camera.zoom = 4.0f;
    camera.offset = { windowWidth / 2.0f, windowHeight / 2.0f };

    TextureManager::loadTexture("dirt1", "images/dirt1.png");
    TextureManager::loadTexture("dirt2", "images/dirt2.png");
    TextureManager::loadTexture("stone", "images/stone.png");
    game.renderMap();


    while (!WindowShouldClose()) {
        SetWindowTitle(("FPS: " + std::to_string(GetFPS())).c_str());
        // std::cout << GetFPS() << std::endl;
        game.update();
        camera.target = game.getPlayer().getPos();

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(background);

        game.draw(camera.zoom);

        EndMode2D();
        EndDrawing();
    }

    TextureManager::unloadAll();
    return 0;
}
