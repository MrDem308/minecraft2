#include "player.h"
#include "map.h"
#include <iostream>

Player::Player(float x, float y, float w, float h) {
    shape.setSize({w, h});
    shape.setPosition({x, y});
    shape.setFillColor(sf::Color::Green);
}

void Player::handleInput() {
    velocity.x = 0; // сброс горизонтальной скорости

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        std::cout << "a" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        velocity.x = moveSpeed;
        std::cout << "d" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        velocity.y = jumpStrength;
        onGround = false;
    }
}

void Player::applyPhysics(const TileMap& map) {
    velocity.y += gravity; // гравитация

    shape.move(velocity);   // двигаем игрока
    resolveCollisions(map); // проверка коллизий
}

void Player::resolveCollisions(const TileMap& map) {
    sf::FloatRect playerBox = shape.getGlobalBounds();
    int ts = map.getTileSize(); // добавь getter в TileMap

    int leftTile = (playerBox.size.x + 0.0f) / ts;
    int rightTile = (playerBox.size.x + 15.0f) / ts;
    int topTile = (playerBox.size.y + 0.0f) / ts;
    int bottomTile = (playerBox.size.y + 15.0f) / ts;

    onGround = false;

    for (int y = topTile; y <= bottomTile; ++y) {
        for (int x = leftTile; x <= rightTile; ++x) {
            int tile = map.getTile(x, y);
            if (tile == 0) continue; // пустота

            sf::FloatRect tileRect({
                static_cast<float>(x * ts),
                static_cast<float>(y * ts)}, {
                    static_cast<float>(ts),
                    static_cast<float>(ts)});

            if (playerBox.findIntersection(tileRect)) {
                sf::FloatRect intersection;
                playerBox.findIntersection(intersection);

                // корректируем позицию
                if (intersection.size.x < intersection.size.y) {
                    if (playerBox.size.x < tileRect.size.x)
                        shape.move({-intersection.size.x, 0});
                    else
                        shape.move({intersection.size.x, 0});
                } else {
                    if (playerBox.size.y < tileRect.size.y) {
                        shape.move({0, -intersection.size.y});
                        velocity.y = 0;
                        onGround = true;
                    } else {
                        shape.move({0, intersection.size.y});
                        velocity.y = 0;
                    }
                }

                playerBox = shape.getGlobalBounds(); // обновляем границы
            }
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}