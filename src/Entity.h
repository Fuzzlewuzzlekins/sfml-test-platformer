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
        void updateFrame();
        void updateFacing();
        void drawToWindow(sf::RenderWindow &window);
        void setPosition(float x, float y);
        // void moveInTime(float seconds);
        void move(const sf::Vector2f &offset);
        void move(float offsetX, float offsetY);
        void setAnimationState(Animation state);
        void setDirection(int direction);
        void setSpeed(float speed);
        Animation getAnimationState();
        int getDirection();
        float getSpeed();
        const sf::Sprite & getSprite();

    private:
        // sf::Texture entTexture;
        sf::IntRect entRect;
        sf::Sprite entSprite;
        float entScale;
        unsigned int entSpeed;
        int entDirection;
        Animation entAnimState;
};