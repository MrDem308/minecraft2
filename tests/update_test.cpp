#include <gtest/gtest.h>
#include "../src/zombie.h"

TEST(ZombieTest, MovesTowardsPlayer) {
    Zombie z(0, 0);
    sf::Vector2f playerPos(100, 0);

    float oldX = z.getPosition().x;
    z.update(1.f, playerPos);

    EXPECT_GT(z.getPosition().x, oldX);
}