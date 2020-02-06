#ifndef UTILS_H
#define UTILS_H
#include <assert.h>

class Utils
{
public:
    static sf::Texture& LoadTexture(std::string fileName)
    {
        sf::Texture* texture = new sf::Texture;
        assert(texture->loadFromFile(fileName));
        
        return *texture;
    }
};

#endif

