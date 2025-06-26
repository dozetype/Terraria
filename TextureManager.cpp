#include "TextureManager.h"

std::map<std::string, Texture2D> TextureManager::textures;
void TextureManager::loadTextures() {
    const FilePathList files = LoadDirectoryFiles("images");
    for (int i = 0; i < files.count; i++) {
        textures[GetFileNameWithoutExt(files.paths[i])] = LoadTexture(files.paths[i]);
    }
}

Texture2D& TextureManager::getTexture(const std::string& name) {
    return textures.at(name);
}

void TextureManager::unloadTextures() {
    for (auto& texture: textures) {
        UnloadTexture(texture.second);
    }
    textures.clear();
}
