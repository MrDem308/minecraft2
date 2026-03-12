#pragma once
#include <SFML/Graphics.hpp>

class Zombie {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    int health = 100;
    int maxHealth = 100;

    float speed = 80.f;
    bool alive = true;

public:
    Zombie(float x, float y);

    void update(float dt, sf::Vector2f playerPos);
    void draw(sf::RenderWindow& window);

    void takeDamage(int dmg);

    bool isAlive() const;
    int getHealth() const;

    bool counted = false;
    bool wasCounted();

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
};