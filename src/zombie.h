#pragma once
#include <SFML/Graphics.hpp>

class Zombie {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    float speed = 60.f;
    float spawnTime;
    bool active = false;

    sf::Clock clock;

    // 💖 здоровье
    int maxHealth = 100;
    int health = 100;

public:
    Zombie(float x, float y, float spawnDelay);

    void update(float dt, sf::Vector2f playerPos);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    int getHealth() const;

    void takeDamage(int dmg); // уменьшаем здоровье
};