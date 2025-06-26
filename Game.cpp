#include "Game.h"

#include "Dirt.h"
#include "TextureManager.h"

Game::Game() {
    Player player;
    gravity = 1;
    blocks = createBlocks();
}

Game::~Game() {
}

void Game::update() {
    player.externalForce({0, gravity});
}

void Game::draw() const {
    player.draw();

    for (auto& block: blocks) {
        block.draw(TextureManager::getTexture("dirt1"));
    }

}

void Game::input() {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        player.moveLeft();
    }else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        player.moveRight();
    }
}

std::vector<Block> Game::createBlocks() {
    std::vector<Block> blocks;
    blocks.push_back(Block({100,100}));
    blocks.push_back(Block({200,100}));
    // blocks.push_back(Dirt({200,100}));
    return blocks;
}
