#include <Field.hpp>
#include <Crop.hpp>
#include <Bacteria.hpp>

#include <gtest/gtest.h>

#include <memory>

class FieldTest : public ::testing::Test
{
};

using core::Bacteria;
using core::Crop;
using core::Field;

TEST(FieldTest, populating_field_with_crops)
{
    int fieldSize{10};
    Field f(fieldSize, fieldSize);

    for (int x = 0; x < fieldSize; ++x)
    {
        for (int y = 0; y < fieldSize; ++y)
        {
            std::string cropSpecie = "açaí" + std::to_string(x + x * y);
            auto crop = std::make_shared<Crop>(cropSpecie, 100);
            f.setCropToTile(crop, x, y);
        }
    }

    for (int x = 0; x < fieldSize; ++x)
    {
        for (int y = 0; y < fieldSize; ++y)
        {
            auto expectedSpecie = "açaí" + std::to_string(x + x * y);
            EXPECT_EQ(f.getCrop(x, y)->specie(), expectedSpecie);
        }
    }
}

TEST(FieldTest, contaminated_crops_will_spread)
{
    int fieldSize{4};
    Field f(fieldSize, fieldSize);

    for (int x = 0; x < fieldSize; ++x)
    {
        for (int y = 0; y < fieldSize; ++y)
        {
            auto crop = std::make_shared<Crop>("açaí", 100);
            f.setCropToTile(crop, x, y);
        }
    }

    auto bac1 = std::make_shared<Bacteria>("bac1");
    auto bac2 = std::make_shared<Bacteria>("bac2");
    f.getCrop(0, 0)->inffectWith(bac1);
    f.getCrop(0, 0)->inffectWith(bac2);

    EXPECT_EQ(f.getCrop(0, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 1)->getAgents().size(), 0);
    EXPECT_EQ(f.getCrop(1, 0)->getAgents().size(), 0);

    f.spreadAgents(); // 1st spread
    EXPECT_EQ(f.getCrop(0, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 1)->getAgents().size(), 0);

    f.spreadAgents(); // 2nd spread
    EXPECT_EQ(f.getCrop(0, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 0)->getAgents().size(), 0);
    EXPECT_EQ(f.getCrop(0, 3)->getAgents().size(), 0);

    f.spreadAgents(); // 3rd spread
    EXPECT_EQ(f.getCrop(0, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 3)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 3)->getAgents().size(), 0);
    EXPECT_EQ(f.getCrop(3, 1)->getAgents().size(), 0);

    f.spreadAgents(); // 4th spread
    EXPECT_EQ(f.getCrop(0, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 3)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 3)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 2)->getAgents().size(), 0);
    EXPECT_EQ(f.getCrop(2, 3)->getAgents().size(), 0);

    f.spreadAgents(); // 5th spread
    EXPECT_EQ(f.getCrop(0, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 3)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 3)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 3)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 3)->getAgents().size(), 0);

    f.spreadAgents(); // 6th spread
    EXPECT_EQ(f.getCrop(0, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 0)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(0, 3)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(1, 3)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 1)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 2)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(2, 3)->getAgents().size(), 2);
    EXPECT_EQ(f.getCrop(3, 3)->getAgents().size(), 2);
}