#include "map.h"
#include <iostream>

TileMap::TileMap(int w, int h, int size)
    : width(w), height(h), tileSize(size)
{
    map.resize(height, std::vector<int>(width, 0));

    if (!dirtTexture.loadFromFile("assets/dirt.png"))
        std::cout << "Failed to load dirt\n";

    if (!grassTexture.loadFromFile("assets/grass_side_carried.png"))
        std::cout << "Failed to load grass\n";

    if (!stoneTexture.loadFromFile("assets/stone.png"))
        std::cout << "Failed to load stone\n";
}

void TileMap::generate()
{
    std::cout << "Map generated\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if (y > height / 1.5)
                map[y][x] = 2;

            if (y > height / 1.5 + 1)
                map[y][x] = 1;

            if (y > height / 1.5 + 6)
                map[y][x] = 3;
        }
    }


}

void TileMap::draw(sf::RenderWindow& window)
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            int tile = map[y][x];
            if (tile == 0)
                continue;

            sf::Sprite sprite(dirtTexture);

            if (tile == 1)
                sprite.setTexture(dirtTexture);
            else if (tile == 2)
                sprite.setTexture(grassTexture);
            else if (tile == 3)
                sprite.setTexture(stoneTexture);

            // 🔥 Масштабирование под TILE_SIZE
            sf::Vector2u texSize = sprite.getTexture().getSize();
            sprite.setScale({
                static_cast<float>(tileSize) / texSize.x,
                static_cast<float>(tileSize) / texSize.y
            });

            sprite.setPosition({
                static_cast<float>(x * tileSize),
                static_cast<float>(y * tileSize)
            });

            window.draw(sprite);
        }
    }
}

int TileMap::getTile(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return -1;

    return map[y][x];
}

void TileMap::setTile(int x, int y, int value)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    map[y][x] = value;
}