#include "Entity.h"

Entity::Entity() {
    entRect = sf::IntRect(0, 0, 16, 32);
    entSprite = sf::Sprite();
    entSprite.setTextureRect(entRect);
    entSprite.setScale(sf::Vector2f(4.f, 4.f));
    entSprite.setOrigin(8.f, 16.f);
    entScale = 4.f;
    entSpeed = 200;
    entDirection = 1;
    entAnimState = idle;
}

Entity::Entity(sf::Texture &texture, int width, int height, float scale) {
    entRect = sf::IntRect(0, 0, width, height);
    entSprite = sf::Sprite(texture, entRect);
    entSprite.setScale(sf::Vector2f(scale, scale));
    entSprite.setOrigin(width/2.f, height/2.f);
    entScale = scale;
    entSpeed = 200;
    entDirection = 1;
    entAnimState = idle;
}

// This is the animation logic that updates the IntRect of the sprite
// based on the current anim state. Each unique animation is assumed
// to take up the same space on the sprite sheet.
void Entity::updateFrame() {
    switch (entAnimState) {
        case walk:
            // Walking: 8 frames looping from (0,0). Start frame doesn't matter.
            entRect.left += 16;
            entRect.left %= 128;
            entRect.top = 0;
            break;
        case sit:
            // Sitting: 5 frames from (0,32), must start there if not already sitting.
            // Transition to sitIdle on final frame (64,32).
            if (entRect.left >= 64 || entRect.top != 32) {
                entRect.left = 0;
                entRect.top = 32;
            } else {
                entRect.left += 16;
                if (entRect.left == 64) {
                    entAnimState = sitIdle;
                }
            }
            break;
        case stand:
            // Standing: 5 frames from (64,32), must start there if not already standing.
            // Transition to idle on final frame (0,32).
            if (entRect.left < 64 || entRect.top != 32) {
                entRect.left = 64;
                entRect.top = 32;
            } else {
                entRect.left += 16;
                if (entRect.left == 128) {
                    entRect.left = 0;
                    entAnimState = idle;
                }
            }
            break;
        case sitIdle:
            entRect.left = 64;
            entRect.top = 32;
            break;
        case idle:
            entRect.left = 0;
            entRect.top = 32;
            break;
        default:
            entRect.left = 0;
            entRect.top = 32;
    }
    // Update sprite's anim frame bounds.
    entSprite.setTextureRect(entRect);
}

// Update sprite's left/right facing.
void Entity::updateFacing() {
    entSprite.setScale(sf::Vector2f(entDirection * entScale, entScale));
}

void Entity::drawToWindow(sf::RenderWindow &window) {
    // // Update sprite's left/right facing and anim frame bounds.
    // entSprite.setScale(sf::Vector2f(entDirection * entScale, entScale));
    // entSprite.setTextureRect(entRect);
    // Draw it!
    window.draw(entSprite);
}

void Entity::setPosition(float x, float y) {
    entSprite.setPosition(x, y);
}

void Entity::move(const sf::Vector2f &offset) {
    entSprite.move(offset);
}

void Entity::move(float offsetX, float offsetY) {
    entSprite.move(offsetX, offsetY);
}

// void Entity::moveInTime(float seconds) {
//     entSprite.move(entDirection * entSpeed * seconds, 0.f);
// }

void Entity::setAnimationState(Animation state){
    entAnimState = state;
}

void Entity::setDirection(int direction) {
    entDirection = direction;
}

void Entity::setSpeed(float speed) {
    entSpeed = speed;
}

Animation Entity::getAnimationState() {
    return entAnimState;
}

int Entity::getDirection() {
    return entDirection;
}

float Entity::getSpeed() {
    return entSpeed;
}

const sf::Sprite & Entity::getSprite() {
    return entSprite;
}

Entity::~Entity() {
    // not sure if needed yet, but probably?
}