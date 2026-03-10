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

public:
    Zombie(float x, float y, float spawnDelay);

    void update(float dt, sf::Vector2f playerPos);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() {
        return sprite.getPosition();
    }
};