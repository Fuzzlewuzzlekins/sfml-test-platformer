#include <iostream>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Entity.h"

int main()
{
    //auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Lysander", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    const int ENT_SPEED = 200; // hero ENT_SPEED in pixels/sec (TODO: move into sprite/character class)
    sf::Clock clock;

    // set up game textures
    sf::Texture heroTexture;
    if (!heroTexture.loadFromFile("../../assets/lysander_temp_sprite.png"))
    {
        // error...
    }

    // Create hero entity (sprite + data) from texture
    Entity hero(heroTexture, 16, 32, 4.f);
    hero.setPosition(400.f, 300.f);

    bool heroCanMove = true;

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
            if (hero.getAnimationState() != sit && hero.getAnimationState() != sitIdle && hero.getAnimationState() != stand) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
                    hero.setAnimationState(walk);
                    hero.setDirection(-1);
                    hero.move(-1.f * hero.getSpeed() * elapsed.asSeconds(), 0.f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
                    hero.setAnimationState(walk);
                    hero.setDirection(1);
                    hero.move(hero.getSpeed() * elapsed.asSeconds(), 0.f);
                } else {
                    hero.setAnimationState(idle);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && hero.getAnimationState() == sitIdle) {
                hero.setAnimationState(stand);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hero.getAnimationState() == idle) {
                hero.setAnimationState(sit);
            }
            hero.updateFacing();
        }

        // Check if it's time to change anim frames
        lastAnimFrame = lastAnimFrame + elapsed;
        if (lastAnimFrame.asSeconds() >= 1.f/ANIM_FRAME_RATE) {
            lastAnimFrame = elapsed;
            hero.updateFrame();
        }

        window.clear();
        // window.draw(heroSprite);
        hero.drawToWindow(window);
        window.display();
    }
}