#include <Organism.hpp>

#include <gtest/gtest.h>

class OrganismTest : public ::testing::Test {};

TEST(OrganismTest, get_quantity_with_zero_present_returns_0)
{
    core::Organism o{}; // organismo with zero nutrients
    EXPECT_EQ(o.takeMineral(core::nutrients::K, 10), 0);
}

TEST(OrganismTest, get_quantity_reduces_present_quantity)
{
    core::Organism o{};
    o.withK(50).withFe(50).withNa(50);
    EXPECT_EQ(o.takeMineral(core::nutrients::K, 20), 20);
    EXPECT_EQ(o.getMineral(core::nutrients::K), 30);

    EXPECT_EQ(o.takeMineral(core::nutrients::Fe, 10), 10);
    EXPECT_EQ(o.getMineral(core::nutrients::Fe), 40);
    
    EXPECT_EQ(o.takeMineral(core::nutrients::Na, 0), 0);
    EXPECT_EQ(o.getMineral(core::nutrients::Na), 50);
}


TEST(OrganismTest, get_quantity_greater_than_present_returns_present)
{
    core::Organism o{}; // organismo with zero nutrients
    o.withK(50).withFe(50).withNa(50);

    EXPECT_EQ(o.takeMineral(core::nutrients::K, 100), 50);
    EXPECT_EQ(o.takeMineral(core::nutrients::Fe, 50), 50);
    EXPECT_EQ(o.takeMineral(core::nutrients::Na, 30), 30);
}