#include "zombie.h"
#include <cmath>

sf::Texture zombieTexture("assets/zombie.png");
Zombie::Zombie(float x, float y, float spawnDelay) : sprite(zombieTexture) {
    spawnTime = spawnDelay;
    sprite.setScale({0.5f, 0.5f});
    sprite.setPosition({x, y});
}

void Zombie::update(float dt, sf::Vector2f playerPos)
{
    if (!active)
    {
        if (clock.getElapsedTime().asSeconds() >= spawnTime)
            active = true;
        else
            return;
    }

    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f direction = playerPos - pos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0)
        direction /= length;

    sprite.move(direction * speed * dt);
}

void Zombie::draw(sf::RenderWindow& window)
{
    if (active)
        window.draw(sprite);
}