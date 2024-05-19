#include <iostream> // not sure if needed yet
#include <SFML/Graphics.hpp>
#include "utils.h"
#include "Entity.h"

Entity::Entity() {
    entRect = new sf::IntRect(0, 0, 16, 32);
    entSprite = new sf::Sprite();
    entSprite.setTextureRect(entRect);
    entSprite.setScale(sf::Vector2f(4.f, 4.f));
    entSprite.setOrigin(8.f, 16.f);
    entScale = 4.f;
    entSpeed = 200;
    entDirection = 1;
    entAnimState = idle;
}

Entity::Entity(sf::Texture &texture, int width, int height, float scale) {
    entRect = new sf::IntRect(0, 0, width, height);
    entSprite = new sf::Sprite(texture, entRect);
    entSprite.setScale(sf::Vector2f(scale, scale);
    entSprite.setOrigin(width/2.f, height/2.f);
    entScale = scale;
    entSpeed = 200;
    entDirection = 1;
    entAnimState = idle;
}

void draw() {

}

Entity::~Entity() {
    // not sure if needed yet, but probably
}