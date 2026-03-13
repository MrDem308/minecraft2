#include "zombie.h"
#include <cmath>

sf::Texture zombieTexture("/Users/mrdem308/Desktop/CLionProjects/minecraft2/assets/zombie.png");;
Zombie::Zombie(float x, float y) : sprite(zombieTexture) {
    sprite.setScale({0.5f, 0.5f});
    sprite.setPosition({x, y});
}

void Zombie::update(float dt, sf::Vector2f playerPos)
{
    if (!alive) return;

    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f dir = playerPos - pos;

    float length = std::sqrt(dir.x*dir.x + dir.y*dir.y);

    if (length != 0)
        dir /= length;

    sprite.move(dir * speed * dt);
}

void Zombie::draw(sf::RenderWindow& window)
{
    if (!alive) return;

    window.draw(sprite);


    float width = 40.f;
    float height = 6.f;

    float percent = float(health) / maxHealth;

    sf::RectangleShape back({width, height});
    back.setFillColor(sf::Color(60,60,60));

    sf::RectangleShape front({width * percent, height});
    front.setFillColor(sf::Color::Red);

    sf::Vector2f pos = sprite.getPosition();

    back.setPosition({pos.x, pos.y - 10});
    front.setPosition({pos.x, pos.y - 10});

    window.draw(back);
    window.draw(front);
}

void Zombie::takeDamage(int dmg)
{
    if (!alive) return;

    health -= dmg;

    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

bool Zombie::isAlive() const
{
    return alive;
}

int Zombie::getHealth() const
{
    return health;
}

sf::Vector2f Zombie::getPosition() const
{
    return sprite.getPosition();
}

bool Zombie::wasCounted()
{
    if (!alive && !counted)
    {
        counted = true;
        return true;
    }
    return false;
}

sf::FloatRect Zombie::getBounds() const
{
    return sprite.getGlobalBounds();
}