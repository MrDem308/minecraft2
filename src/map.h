#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TileMap {
public:
    TileMap(int width, int height, int tileSize);

    void generate();
    void draw(sf::RenderWindow& window);
    int getTile(int x, int y) const;
    void setTile(int x, int y, int value);

    int getTileSize() const {return tileSize;};

private:
    int width;
    int height;
    int tileSize;

    std::vector<std::vector<int>> map;

    sf::Texture dirtTexture;
    sf::Texture grassTexture;
    sf::Texture stoneTexture;
};