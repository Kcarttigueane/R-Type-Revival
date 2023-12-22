#ifndef SPARTSET_TEST_HPP
#define SPARTSET_TEST_HPP

#include <gtest/gtest.h>
#include "../libs/ECS/include/spart_set.hpp"
#include "../libs/ECS/src/components/health.hpp"

TEST(SparseSet, AddingHealthComponents)
{
    SparseSet<HealthComponent> healthSparseSet;

    HealthComponent health1{100, 1.0f, 0.0f};
    HealthComponent health2{150, 1.5f, 0.0f};

    healthSparseSet.add(0, health1);
    healthSparseSet.add(1, health2);

    ASSERT_TRUE(healthSparseSet.has(0));
    ASSERT_TRUE(healthSparseSet.has(1));
    ASSERT_EQ(healthSparseSet.get(0)->get().healthPoints, health1.healthPoints);
    ASSERT_EQ(healthSparseSet.get(1)->get().healthPoints, health2.healthPoints);
}

TEST(SparseSet, RemovingHealthComponents)
{
    SparseSet<HealthComponent> healthSparseSet;

    HealthComponent health1{100, 1.0f, 0.0f};
    HealthComponent health2{150, 1.5f, 0.0f};

    healthSparseSet.add(0, health1);
    healthSparseSet.add(1, health2);

    healthSparseSet.remove(0);

    ASSERT_FALSE(healthSparseSet.has(0));
    ASSERT_TRUE(healthSparseSet.has(1));
    ASSERT_EQ(healthSparseSet.get(1)->get().healthPoints, health2.healthPoints);
}

TEST(SparseSet, ClearingHealthSparseSet)
{
    SparseSet<HealthComponent> healthSparseSet;

    HealthComponent health1{100, 1.0f, 0.0f};
    HealthComponent health2{150, 1.5f, 0.0f};

    healthSparseSet.add(0, health1);
    healthSparseSet.add(1, health2);

    healthSparseSet.clear();

    ASSERT_FALSE(healthSparseSet.has(0));
    ASSERT_FALSE(healthSparseSet.has(1));
}

TEST(SparseSet, IteratingThroughHealthComponents)
{
    SparseSet<HealthComponent> healthSparseSet;

    HealthComponent health1{100, 1.0f, 0.0f};
    HealthComponent health2{150, 1.5f, 0.0f};

    healthSparseSet.add(0, health1);
    healthSparseSet.add(1, health2);

    int count = 0;
    for (const auto& health : healthSparseSet) {
        count++;
        static_cast<void>(health);
    }

    ASSERT_EQ(count, healthSparseSet.getSize());
}

TEST(SparseSet, MixedOperations)
{
    SparseSet<HealthComponent> healthSparseSet;

    Entity entity1 = 0;
    Entity entity2 = 1;

    HealthComponent health1{100, 1.0f, 0.0f};
    HealthComponent health2{150, 1.5f, 0.0f};

    healthSparseSet.add(entity1, health1);
    healthSparseSet.add(entity2, health2);

    ASSERT_TRUE(healthSparseSet.has(entity1));
    ASSERT_TRUE(healthSparseSet.has(entity2));

    healthSparseSet.remove(entity1);

    ASSERT_FALSE(healthSparseSet.has(entity1));
    ASSERT_TRUE(healthSparseSet.has(entity2));

    healthSparseSet.clear();

    ASSERT_FALSE(healthSparseSet.has(entity1));
    ASSERT_FALSE(healthSparseSet.has(entity2));

    HealthComponent health3{120, 1.2f, 0.0f};
    HealthComponent health4{180, 1.8f, 0.0f};

    healthSparseSet.add(entity1, health3);
    healthSparseSet.add(entity2, health4);

    int count = 0;
    for (const auto& health : healthSparseSet) {
        count++;
        static_cast<void>(health);
    }
    ASSERT_EQ(count, healthSparseSet.getSize());
}

#endif  // SPARTSET_TEST_HPP