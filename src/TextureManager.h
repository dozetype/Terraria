#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <raylib.h>
#include <unordered_map>
#include <string>



class TextureManager {
public:
    static void loadTexture(const std::string& name, const std::string& path);
    static Texture2D getTexture(const std::string& name);
    static void unloadAll();

private:
    static std::unordered_map<std::string, Texture2D> textures;
};


#endif //TEXTUREMANAGER_H
