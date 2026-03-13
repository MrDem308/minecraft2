#include <gtest/gtest.h>
#include "../src/zombie.h"

TEST(ZombieTest, TakesDamage)
{
    Zombie z(0,0);

    int hp = z.getHealth();

    z.takeDamage(10);

    EXPECT_EQ(z.getHealth(), hp - 10);
}