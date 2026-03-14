#include <gtest/gtest.h>
#include "../src/zombie.h"


TEST(ZombieTest, DiesWhenKilled) {
    Zombie z(0, 0);
    EXPECT_TRUE(z.isAlive());

    z.takeDamage(100);
    EXPECT_FALSE(z.isAlive());
}