#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"

class Player {
public:
    Player(float x, float y, float w, float h);

    void handleInput();
    void applyPhysics(const TileMap& map);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    float moveSpeed = 3.0f;
    float gravity = 0.5f;
    float jumpStrength = -10.0f;
    bool onGround = false;

    void resolveCollisions(const TileMap& map);
};