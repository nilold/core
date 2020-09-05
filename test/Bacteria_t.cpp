#include <Bacteria.hpp>
#include <Substract.hpp>

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

    core::Substract poorSubstract;
    bac.cycle(poorSubstract);
    ASSERT_EQ(bac.getHealth(), 0);
}

TEST(BacteriaTest, bacteria_perishes_if_not_enough_nutrients)
{
    int health = 100;
    int ironNeed = 10;

    core::Bacteria bac("Bac 1", health);
    bac.needs(Minerals::Fe, ironNeed);

    core::Substract poorSubstract;
    poorSubstract.withFe(ironNeed / 2);

    bac.cycle(poorSubstract);
    ASSERT_LT(bac.getHealth(), health);
    ASSERT_GT(bac.getHealth(), 0);
}

TEST(BacteriaTest, bacteria_also_dies_with_partially_unsitisfied)
{
    int health = 100;
    int ironNeed = 10;
    int nitrogeniumNeed = 10;

    core::Bacteria bac("Bac 1", health);
    bac.needs(Minerals::Fe, ironNeed)
        .needs(Minerals::N, nitrogeniumNeed);

    core::Substract poorSubstract;
    poorSubstract.withFe(ironNeed);

    bac.cycle(poorSubstract);
    ASSERT_EQ(bac.getHealth(), 0);
}

TEST(BacteriaTest, bacteria_is_happy_if_gets_everything_it_needs)
{
    int health = 100;
    int ironNeed = 10;
    int nitrogeniumNeed = 10;

    core::Bacteria bac("Bac 1", health);
    bac.needs(Minerals::Fe, ironNeed)
        .needs(Minerals::N, nitrogeniumNeed);

    core::Substract substract;
    substract.withFe(ironNeed)
        .withN(nitrogeniumNeed * 2)
        .withNa(200);

    bac.cycle(substract);
    ASSERT_EQ(bac.getHealth(), health);
}

TEST(BacteriaTest, bacteria_can_make_a_independent_copy_itself)
{
    int health = 100;
    int ironNeed = 10;
    int nitrogeniumNeed = 10;

    core::Bacteria bac("Bac 1", health);
    bac.needs(Minerals::Fe, ironNeed)
        .needs(Minerals::N, nitrogeniumNeed);

    auto bacCpy = std::dynamic_pointer_cast<core::Bacteria>(bac.selfCopy());

    EXPECT_EQ(bacCpy->getHealth(), health);

    core::Substract substract;
    bac.cycle(substract);
    bac.cycle(substract);
    bac.cycle(substract);

    EXPECT_EQ(bacCpy->getHealth(), health);
}