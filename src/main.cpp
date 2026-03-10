#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "player.h"
#include "zombie.h"

int main()
{
    const int TILE_SIZE = 32;
    const int MAP_WIDTH = 25;
    const int MAP_HEIGHT = 18;

    sf::Vector2f velocity; // velocity.x — горизонтальная, velocity.y — вертикальная
    float gravity = 0.5f;    // сила гравитации
    float jumpStrength = -10; // отрицательное — вверх
    float moveSpeed = 10;      // скорость ходьбы
    velocity.x = 10; // сброс горизонтальной скорости

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Minecraft 2D");

    TileMap map(MAP_WIDTH, MAP_HEIGHT, TILE_SIZE);
    map.generate();

    Zombie zombie(200, 120, 5.f);
    sf::Clock clock;

    Player player(100, 100, 28, 28);

    // Load a sprite to display
    sf::Image skin("assets/player.png");
    sf::Texture texture(skin);
    sf::Sprite sprite(texture);
    sprite.setScale({0.5f, 0.5f});\
    sprite.setPosition({0.0f, 0.0f});

    // Create a graphical text to display
    const sf::Font font("assets/minecraft-ten-font-cyrillic.ttf");
    sf::Text text(font, "MINECRAFT 2", 50);

    sf::Texture dirtTexture;
    sf::Texture grassTexture;

    if (!dirtTexture.loadFromFile("assets/dirt.png"))
        std::cout << "Failed to load dirt\n";

    if (!grassTexture.loadFromFile("assets/grass_side_carried.png"))
        std::cout << "Failed to load grass\n";

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                    sprite.move({0, -5});
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    skin.flipHorizontally();
                    sprite.move({-5, 0});
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                    sprite.move({0, 5});
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                    sprite.move({5, 0});
                }
            }

            if ((sprite.getPosition().y >= 125 && sprite.getPosition().x < 320) || (sprite.getPosition().y >= 150 && sprite.getPosition().x >= 320)) {
                    std::cout << "collision" << std::endl;
                    sprite.move({0,-5});
            }
        }
        float dt = clock.restart().asSeconds();

        zombie.update(dt, sprite.getPosition());

        player.applyPhysics(map);

            // Clear screen
        sf::Color sky = sf::Color::Black;
        window.clear(sky);

        map.draw(window);
        player.draw(window);
        window.draw(sprite);
        window.draw(text);
        zombie.draw(window);
        map.draw(window);

        window.display();
    }
}
