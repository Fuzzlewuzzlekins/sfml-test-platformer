#include <iostream> // not sure if needed yet
#include <SFML/Graphics.hpp>
#include "utils.h"

class Entity {
    public:
        Entity();
        ~Entity();
        Entity(sf::Texture &texture, int width, int height, float scale);
        // Entity(const Entity &E); - don't think I need this
        // Entity & operator=(const Entity &E); - or this?
        void draw();

    private:
        // sf::Texture entTexture;
        sf::IntRect entRect;
        sf::Sprite entSprite;
        float entScale;
        unsigned int entSpeed;
        int entDirection;
        Animation entAnimState;
}