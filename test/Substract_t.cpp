#include <Substract.hpp>

#include <gtest/gtest.h>

class SubstractTest : public ::testing::Test {};

TEST(SubstractTest, take_quantity_with_zero_present_returns_0)
{
    core::Substract o{};
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::K, 10), 0);
}

TEST(SubstractTest, adding_quantity_of_type_increase_present_quantity)
{
    core::Substract o{};
    o.addNutrient(core::nutrients::Minerals::K, 60);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::K), 60);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::N), 0);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::Na), 0);
}

TEST(SubstractTest, get_quantity_reduces_present_quantity)
{
    core::Substract o{};
    o.withK(50).withFe(50).withNa(50);
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::K, 20), 20);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::K), 30);

    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::Fe, 10), 10);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::Fe), 40);
    
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::Na, 0), 0);
    EXPECT_EQ(o.getNutrient(core::nutrients::Minerals::Na), 50);
}


TEST(SubstractTest, get_quantity_greater_than_present_returns_present)
{
    core::Substract o{}; // Substracto with zero nutrients
    o.withK(50).withFe(50).withNa(50);

    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::K, 100), 50);
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::Fe, 51), 50);
    EXPECT_EQ(o.takeNutrient(core::nutrients::Minerals::Na, 30), 30);
}

// TEST(SubstractTest. tmpTest)
// {

// }