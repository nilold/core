#include <Organism.hpp>

#include <gtest/gtest.h>

class OrganismTest : public ::testing::Test {};

TEST(OrganismTest, take_quantity_with_zero_present_returns_0)
{
    core::Organism o{};
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::K, 10), 0);
}

TEST(OrganismTest, adding_quantity_of_type_increase_present_quantity)
{
    core::Organism o{};
    o.addNutrient(core::nutrients::Minerals::K, 60);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::K), 60);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::N), 0);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::Na), 0);
}

TEST(OrganismTest, get_quantity_reduces_present_quantity)
{
    core::Organism o{};
    o.withK(50).withFe(50).withNa(50);
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::K, 20), 20);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::K), 30);

    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::Fe, 10), 10);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::Fe), 40);
    
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::Na, 0), 0);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::Na), 50);
}


TEST(OrganismTest, get_quantity_greater_than_present_returns_present)
{
    core::Organism o{}; // organismo with zero nutrients
    o.withK(50).withFe(50).withNa(50);

    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::K, 100), 50);
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::Fe, 51), 50);
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::Na, 30), 30);
}