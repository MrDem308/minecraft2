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

    Zombie zombie(800, 120, 5.f);
    sf::Clock clock;

    sf::RectangleShape healthBarBack({200.f, 20.f});
    healthBarBack.setFillColor(sf::Color(100, 100, 100));
    healthBarBack.setPosition({300.f, 20.f}); // сверху экрана

    sf::RectangleShape healthBarFront({200.f, 20.f});
    healthBarFront.setFillColor(sf::Color::Red);
    healthBarFront.setPosition({300.f, 20.f});

    Player player(100, 100, 28, 28);

    // Load a sprite to display
    sf::Image skin("assets/player.png");
    sf::Texture texture(skin);
    sf::Sprite sprite(texture);
    sprite.setScale({0.5f, 0.5f});\
    sprite.setPosition({0.0f, 0.0f});

    const sf::Font font("assets/minecraft-ten-font-cyrillic.ttf");

    sf::Text deathText(font, "YOU DIED!");
    deathText.setCharacterSize(50);
    deathText.setFillColor(sf::Color::Red);
    deathText.setPosition({100.f, 100.f}); // настраиваем на центр экрана

    // Create a graphical text to display
    sf::Text text(font, "MINECRAFT 2", 50);

    sf::Texture dirtTexture;
    sf::Texture grassTexture;

    if (!dirtTexture.loadFromFile("assets/dirt.png"))
        std::cout << "Failed to load dirt\n";

    if (!grassTexture.loadFromFile("assets/grass_side_carried.png"))
        std::cout << "Failed to load grass\n";

    while (window.isOpen()) {
        // Process events
        while (const std::optional event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    if (zombie.getHealth() > 0) {
                        zombie.takeDamage(10); // каждый клик -10 здоровья
                        std::cout << zombie.getHealth() << std::endl;
                    }
                }
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

            if ((sprite.getPosition().y >= 125)) {
                    std::cout << "collision" << std::endl;
                    sprite.move({0,-5});
            }
        }
        float dt = clock.restart().asSeconds();
        zombie.update(dt, sprite.getPosition());

        // обновляем босс-бар
        float healthPercent = float(zombie.getHealth()) / 100.f;
        healthBarFront.setSize({200.f * healthPercent, 20.f});

        zombie.update(dt, sprite.getPosition());

        sf::Vector2f playerPos = sprite.getPosition();
        sf::Vector2f zombiePos = zombie.getPosition();

        float dx = zombiePos.x - playerPos.x;
        float dy = zombiePos.y - playerPos.y;
        float distance = std::sqrt(dx*dx + dy*dy);

        sf::Color sky = sf::Color::Cyan;
        window.clear(sky);

        map.draw(window);
        player.draw(window);
        window.draw(sprite);
        zombie.draw(window);
        window.draw(text);
        map.draw(window);

        if (distance < 100.f) {
            window.draw(deathText);
        }

        window.draw(healthBarBack);
        window.draw(healthBarFront);

        window.display();
    }
}
