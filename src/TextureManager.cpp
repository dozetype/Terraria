#include "TextureManager.h"
#include <stdexcept>

std::unordered_map<std::string, Texture2D> TextureManager::textures;

void TextureManager::loadTexture(const std::string& name, const std::string& path) {
    if (textures.find(name) == textures.end()) {
        Texture2D tex = LoadTexture(path.c_str());
        if (tex.id == 0) {
            throw std::runtime_error("Failed to load texture: " + path);
        }
        textures[name] = tex;
    }
}

Texture2D TextureManager::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it == textures.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return it->second;
}

void TextureManager::unloadAll() {
    for (auto& [name, tex] : textures) {
        UnloadTexture(tex);
    }
    textures.clear();
}