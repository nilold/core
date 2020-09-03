#include <Crop.hpp>
#include <Bacteria.hpp>

#include <gtest/gtest.h>
#include <memory>

class CropTest : public ::testing::Test
{
};

using core::Bacteria;
using core::Crop;
using core::nutrients::Minerals;

TEST(CropTest, crop_inffected_with_humble_bacteria_keeps_nutrients)
{
    auto bac1 = std::make_shared<Bacteria>("bac1");

    int cropHealth = 100;
    Crop crop1("Pequi", cropHealth);

    crop1.withFe(10).withK(10).withN(10).withNa(10);
    crop1.inffectWith(bac1);
    crop1.cycle();
    crop1.cycle();
    crop1.cycle();

    EXPECT_EQ(crop1.getNutrient(Minerals::Fe), 10);
    EXPECT_EQ(crop1.getNutrient(Minerals::K), 10);
    EXPECT_EQ(crop1.getNutrient(Minerals::N), 10);
    EXPECT_EQ(crop1.getNutrient(Minerals::Na), 10);
}

TEST(CropTest, crop_inffected_with_eager_bacteria_loses_nutrients)
{
    auto bac1 = std::make_shared<Bacteria>("bac1");
    bac1->needs(Minerals::Fe, 1)
        .needs(Minerals::K, 1)
        .needs(Minerals::N, 1)
        .needs(Minerals::Na, 1);

    int cropHealth = 100;
    Crop crop1("Pequi", cropHealth);

    crop1.withFe(10).withK(10).withN(10).withNa(10);
    crop1.inffectWith(bac1);
    crop1.cycle();
    crop1.cycle();
    crop1.cycle();

    EXPECT_GT(crop1.getNutrient(Minerals::Fe), 0);
    EXPECT_GT(crop1.getNutrient(Minerals::K), 0);
    EXPECT_GT(crop1.getNutrient(Minerals::N), 0);
    EXPECT_GT(crop1.getNutrient(Minerals::Na), 0);

    EXPECT_LT(crop1.getNutrient(Minerals::Fe), 10);
    EXPECT_LT(crop1.getNutrient(Minerals::K), 10);
    EXPECT_LT(crop1.getNutrient(Minerals::N), 10);
    EXPECT_LT(crop1.getNutrient(Minerals::Na), 10);
}

TEST(CropTest, crop_inffected_with_bacteria_loses_health)
{
    auto bac1 = std::make_shared<Bacteria>("bac1");
    bac1->needs(Minerals::Fe, 1);

    int cropHealth = 100;
    Crop crop1("Pequi", cropHealth);
    crop1.needs(Minerals::Fe, 10).withFe(10);
    crop1.inffectWith(bac1);

    crop1.cycle();
    crop1.cycle();
    crop1.cycle();

    EXPECT_LT(crop1.health(), cropHealth);
}

TEST(CropTest, but_if_it_doesnt_need_mineral_its_ok)
{
    auto bac1 = std::make_shared<Bacteria>("bac1");
    bac1->needs(Minerals::Fe, 1);

    int cropHealth = 100;
    Crop crop1("Pequi", cropHealth);
    crop1.needs(Minerals::Na, 10).withNa(10);
    crop1.inffectWith(bac1);

    crop1.cycle();
    crop1.cycle();
    crop1.cycle();

    EXPECT_EQ(crop1.health(), cropHealth);
}

TEST(CropTest, crop_recovers_if_has_minerals_but_never_more_than_max)
{
    auto bac1 = std::make_shared<Bacteria>("bac1");
    bac1->needs(Minerals::Fe, 1);

    int cropHealth = 100;
    int maxCropHealth = 100;
    Crop crop1("Pequi", cropHealth, maxCropHealth);
    crop1.needs(Minerals::Fe, 10).withFe(10);
    crop1.inffectWith(bac1);

    // First cycle: bacteria will deteriorate crop's healt
    crop1.cycle();
    int currentHealth = crop1.health();
    EXPECT_LT(currentHealth, cropHealth);

    // now we add more mineral than it needs, so it will recover
    crop1.addNutrient(Minerals::Fe, 10);
    crop1.cycle();

    int newHealth = crop1.health();
    EXPECT_GT(newHealth, currentHealth);
    EXPECT_LE(newHealth, maxCropHealth); // but never more than max

    crop1.addNutrient(Minerals::Fe, 10);
    crop1.cycle();

    EXPECT_GE(crop1.health(), newHealth);
    EXPECT_LE(crop1.health(), maxCropHealth);

    // But if we dont act somehow, eventually it will die
    // Warning: this test will fail if/when we add immunologic system
    bac1->needs(Minerals::Fe, 3);

    int it = 0;
    while (crop1.health() > 0 && it < 20)
        crop1.cycle();

    EXPECT_EQ(crop1.health(), 0);
}

TEST(CropTest, healthy_crop_develops_after_enough_cyles)
{
    int cropHealth = 100;
    int maxCropHealth = 100;
    int healthDevelopThreshold = 80;
    int cyclesPerStage = 5;
    Crop crop("Pequi", cropHealth, maxCropHealth, healthDevelopThreshold, cyclesPerStage);

    EXPECT_EQ(crop.phenologicalStage(), 0);

    for (int i = 0; i < cyclesPerStage; ++i)
        crop.cycle();

    EXPECT_EQ(crop.phenologicalStage(), 1);
}

TEST(CropTest, unhealthy_crop_wont_develop)
{
    int cropHealth = 50;
    int maxCropHealth = 100;
    int healthDevelopThreshold = 80;
    int cyclesPerStage = 5;
    Crop crop("Pequi", cropHealth, maxCropHealth, healthDevelopThreshold, cyclesPerStage);

    EXPECT_EQ(crop.phenologicalStage(), 0);

    for (int i = 0; i < 2 * cyclesPerStage; ++i)
        crop.cycle();

    EXPECT_EQ(crop.phenologicalStage(), 0);
}