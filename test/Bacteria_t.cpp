#include <Bacteria.hpp>
#include <Organism.hpp>

#include <gtest/gtest.h>

class BacteriaTest : public ::testing::Test
{
};

using core::nutrients::Minerals;

TEST(BacteriaTest, bacteria_dies_if_no_nutrients)
{
    int health = 100;
    int ironNeed = 10;

    core::Bacteria bac("Bac 1", health);
    bac.needs(Minerals::Fe, ironNeed);
    ASSERT_EQ(bac.getHealth(), 100);

    core::Organism poorOrganism;
    bac.live(poorOrganism);
    ASSERT_EQ(bac.getHealth(), 0);
}

TEST(BacteriaTest, bacteria_perishes_if_not_enough_nutrients)
{
    int health = 100;
    int ironNeed = 10;

    core::Bacteria bac("Bac 1", health);
    bac.needs(Minerals::Fe, ironNeed);

    core::Organism poorOrganism;
    poorOrganism.withFe(ironNeed / 2);

    bac.live(poorOrganism);
    ASSERT_LT(bac.getHealth(), health);
    ASSERT_GT(bac.getHealth(), 0);
}

TEST(BacteriaTest, bacteria_also_dies_with_partially_unsitisfied)
{
    int health = 100;
    int ironNeed = 10;
    int nitrogeniumNeed = 10;
    
    core::Bacteria bac("Bac 1", health);
    bac .needs(Minerals::Fe, ironNeed)
        .needs(Minerals::N, nitrogeniumNeed);

    core::Organism poorOrganism;
    poorOrganism.withFe(ironNeed);

    bac.live(poorOrganism);
    ASSERT_EQ(bac.getHealth(), 0);
}

TEST(BacteriaTest, bacteria_is_happy_if_gets_everything_it_needs)
{
    int health = 100;
    int ironNeed = 10;
    int nitrogeniumNeed = 10;

    core::Bacteria bac("Bac 1", health);
    bac .needs(Minerals::Fe, ironNeed)
        .needs(Minerals::N, nitrogeniumNeed);

    core::Organism organism;
    organism.withFe(ironNeed)
            .withN(nitrogeniumNeed * 2)
            .withNa(200);

    bac.live(organism);
    ASSERT_EQ(bac.getHealth(), health);
}
