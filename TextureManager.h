#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <map>
#include <raylib.h>


class TextureManager {
public:
    static void loadTextures();
    static Texture2D& getTexture(const std::string& name);
    static void unloadTextures();

private:
    static std::map<std::string, Texture2D> textures;
};



#endif //TEXTUREMANAGER_H
