#include <gtest/gtest.h>
#include "../src/zombie.h"

TEST(ZombieTest, SpawnMultipleZombies) {
    std::vector<Zombie> zombies;
    zombies.emplace_back(0,0);
    zombies.emplace_back(20,20);
    zombies.emplace_back(40,40);
    zombies.emplace_back(60,60);
    EXPECT_EQ(zombies.size(), 4);
}