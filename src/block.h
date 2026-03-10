#include <SFML/Graphics.hpp>

Block::Block(float x, float y, sf::Color color) {
    shape.setSize(sf::Vector2f(32, 32));
    shape.setPosition(x, y);
    shape.setFillColor(color);
}

void Block::draw(sf::RenderWindow &window) {
    window.draw(shape);
}