#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils.h"
#include "TileMap.h"

int main()
{
    //auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Lysander", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    const int HERO_SPEED = 200; // hero HERO_SPEED in pixels/sec (TODO: move into sprite/character class)
    sf::Clock clock;

    // set up game textures
    sf::Texture heroTexture;
    if (!heroTexture.loadFromFile("../../assets/lysander_temp_sprite.png"))
    {
        // error...
    }
    // create sprites from textures (TODO: move to class)
    sf::IntRect rectSourceHeroSprite(0, 0, 16, 32);
    sf::Sprite heroSprite(heroTexture, rectSourceHeroSprite);
    const float SPRITE_SCALE = 4.f;
    heroSprite.setScale(sf::Vector2f(SPRITE_SCALE, SPRITE_SCALE));
    heroSprite.setOrigin(8.f, 16.f); // TODO: base this on width/height
    heroSprite.setPosition(400.f, 300.f);
    
    Animation heroAnimState = idle;
    int heroAnimDir = 1;
    bool heroCanMove = true;

    // sf::Time lastAnimFrame = new sf::Time();
    auto lastAnimFrame = sf::Time{};
    const int ANIM_FRAME_RATE = 10;

    sf::View gameView = window.getDefaultView();
    window.setView(gameView);

    while (window.isOpen())
    {
        // Get elapsed time since previous frame
        sf::Time elapsed = clock.restart();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Prevent hero control input if window out of focus. 
        // TODO: expand to include menus and cutscenes.
        heroCanMove = window.hasFocus();

        if (heroCanMove) {
            // move hero according to key presses, if able
            if (heroAnimState != sit && heroAnimState != sitIdle && heroAnimState != stand) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
                    heroAnimState = walk;
                    heroAnimDir = -1;
                    heroSprite.move(-1.f * HERO_SPEED * elapsed.asSeconds(), 0.f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
                    heroAnimState = walk;
                    heroAnimDir = 1;
                    heroSprite.move(HERO_SPEED * elapsed.asSeconds(), 0.f);
                } else {
                    heroAnimState = idle;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && heroAnimState == sitIdle) {
                heroAnimState = stand;
                // heroSprite.move(0.f, -1.f * HERO_SPEED * elapsed.asSeconds());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && heroAnimState == idle) {
                heroAnimState = sit;
                // heroSprite.move(0.f, HERO_SPEED * elapsed.asSeconds());
            }
        }
        

        // Check if it's time to change anim frames
        // This is a temp hack... will need to move to animation manager
        lastAnimFrame = lastAnimFrame + elapsed;
        if (lastAnimFrame.asSeconds() >= 1.f/ANIM_FRAME_RATE) {
            lastAnimFrame = elapsed;
            switch (heroAnimState) {
                case walk:
                    rectSourceHeroSprite.left += 16;
                    rectSourceHeroSprite.left %= 128;
                    rectSourceHeroSprite.top = 0;
                    break;
                case sit:
                    if (rectSourceHeroSprite.left >= 64 || rectSourceHeroSprite.top != 32) {
                        rectSourceHeroSprite.left = 0;
                        rectSourceHeroSprite.top = 32;
                    } else {
                        rectSourceHeroSprite.left += 16;
                        if (rectSourceHeroSprite.left == 64) {
                            heroAnimState = sitIdle;
                        }
                    }
                    break;
                case stand:
                    if (rectSourceHeroSprite.left < 64 || rectSourceHeroSprite.top != 32) {
                        rectSourceHeroSprite.left = 64;
                        rectSourceHeroSprite.top = 32;
                    } else {
                        rectSourceHeroSprite.left += 16;
                        if (rectSourceHeroSprite.left == 128) {
                            rectSourceHeroSprite.left = 0;
                            heroAnimState = idle;
                        }
                    }
                    break;
                case sitIdle:
                    rectSourceHeroSprite.left = 64;
                    rectSourceHeroSprite.top = 32;
                    break;
                case idle:
                    rectSourceHeroSprite.left = 0;
                    rectSourceHeroSprite.top = 32;
                    break;
                default:
                    rectSourceHeroSprite.left = 0;
                    rectSourceHeroSprite.top = 32;
            }
            heroSprite.setScale(sf::Vector2f(heroAnimDir * SPRITE_SCALE, SPRITE_SCALE));
            heroSprite.setTextureRect(rectSourceHeroSprite);
        }

        window.clear();
        // window.draw(shape);
        window.draw(heroSprite);
        window.display();
    }
}