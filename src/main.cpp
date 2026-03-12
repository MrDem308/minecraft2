#include <iostream>
#include <random>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "player.h"
#include "zombie.h"
#include <vector>

int main()
{
    const int TILE_SIZE = 32;
    const int MAP_WIDTH = 60;
    const int MAP_HEIGHT = 33;
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Minecraft 2D");

    TileMap map(MAP_WIDTH, MAP_HEIGHT, TILE_SIZE);
    map.generate();

    sf::Clock clock;

    sf::RectangleShape healthBarBack({200.f, 20.f});
    healthBarBack.setFillColor(sf::Color(100, 100, 100));
    healthBarBack.setPosition({300.f, 20.f});

    sf::RectangleShape healthBarFront({200.f, 20.f});
    healthBarFront.setFillColor(sf::Color::Red);
    healthBarFront.setPosition({300.f, 20.f});

    int counter = 0;
    bool gameOver = false;
    Player player(100, 100, 28, 28);

    sf::Image skin("assets/player.png");
    sf::Texture texture(skin);
    sf::Sprite sprite(texture);
    sprite.setScale({0.5f, 0.5f});\
    sprite.setPosition({0.0f, 0.0f});

    const sf::Font font("assets/minecraft-ten-font-cyrillic.ttf");

    sf::Text deathText(font, "GAME OVER!");
    deathText.setCharacterSize(100);
    deathText.setFillColor(sf::Color::Red);
    deathText.setPosition({500.f, 400.f});

    sf::Text counterText(font, "", 30);
    counterText.setFillColor(sf::Color::White);
    counterText.setPosition({10.f, 60.f});

    sf::Text text(font, "MINECRAFT 2", 50);

    sf::Texture dirtTexture;
    sf::Texture grassTexture;

    if (!dirtTexture.loadFromFile("assets/dirt.png"))
        std::cout << "Failed to load dirt\n";

    if (!grassTexture.loadFromFile("assets/grass_side_carried.png"))
        std::cout << "Failed to load grass\n";

    bool zombieDead = false;

    std::vector<Zombie> zombies;

    sf::Clock spawnClock;
    float spawnDelay = 5.f;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> xDist(0, MAP_WIDTH * TILE_SIZE);
    std::uniform_int_distribution<> yDist(0, MAP_HEIGHT * TILE_SIZE);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

                    for (auto& z : zombies) {

                        float dx = z.getPosition().x - sprite.getPosition().x;
                        float dy = z.getPosition().y - sprite.getPosition().y;

                        float distance = std::sqrt(dx*dx + dy*dy);

                        if (distance < 150.f && z.isAlive()) {
                            z.takeDamage(20);
                        }

                        if (!z.isAlive() && z.wasCounted()) {
                            counter++;
                        }
                    }

                }
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                    sprite.move({0, -15});
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    skin.flipHorizontally();
                    sprite.move({-15, 0});
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                    sprite.move({0, 15});
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                    sprite.move({15, 0});
                }
            }

        }
        float dt = clock.restart().asSeconds();
        for (auto& z : zombies) {
            z.update(dt, sprite.getPosition());

            float dx = z.getPosition().x - sprite.getPosition().x;
            float dy = z.getPosition().y - sprite.getPosition().y;
            float distance = std::sqrt(dx*dx + dy*dy);

            if (distance < 80.f && z.isAlive()) {
                gameOver = true;
            }
        }

        if (spawnClock.getElapsedTime().asSeconds() > spawnDelay) {

            float x = xDist(gen);
            float y = yDist(gen);

            zombies.emplace_back(x, y);

            spawnClock.restart();
        }

        sf::Vector2f playerPos = sprite.getPosition();

        if (!gameOver) {

            sf::Color sky = sf::Color::Cyan;
            window.clear(sky);

            map.draw(window);
            player.draw(window);
            window.draw(sprite);
            window.draw(text);
            map.draw(window);

            for (auto& z : zombies) {
                if (z.getHealth() > 0) {
                    z.draw(window);
                }
            }

            counterText.setString("Kills: " + std::to_string(counter));
            window.draw(counterText);

            window.display();
        }

        if (gameOver) {

            sf::Color deathScreen = sf::Color::Black;
            window.clear(deathScreen);

            window.draw(deathText);

            window.display();
        }
    }
}