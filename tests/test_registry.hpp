#ifndef REGISTRY_TEST_HPP
#define REGISTRY_TEST_HPP

#include <gtest/gtest.h>
#include "../libs/ECS/include/registry.hpp"
#include "../libs/ECS/src/components/health.hpp" 

TEST(Registry, CreateAndDestroyEntity) {
    Registry registry;
    Entity entity1 = registry.createEntity();
    Entity entity2 = registry.createEntity();

    EXPECT_EQ(entity1, 0);
    EXPECT_EQ(entity2, 1);

    registry.destroyEntity(entity1);
}

TEST(Registry, AddAndRetrieveComponent) {
    Registry registry;
    Entity entity = registry.createEntity();
    registry.emplace<HealthComponent>(entity, 100.0f, 100.0f, 100.0f);
    HealthComponent* healthComponent = registry.getComponent<HealthComponent>(entity);
    ASSERT_NE(healthComponent, nullptr);
    EXPECT_EQ(healthComponent->getHealth(), 100.0f);
    registry.removeComponent<HealthComponent>(entity);
    healthComponent = registry.getComponent<HealthComponent>(entity);
    EXPECT_EQ(healthComponent, nullptr);
}

TEST(Registry, RemoveDestroyedEntityComponents) {
    Registry registry;
    Entity entity = registry.createEntity();
    registry.emplace<HealthComponent>(entity, 100.0f, 100.0f, 100.0f);
    registry.destroyEntity(entity);
    HealthComponent* healthComponent = registry.getComponent<HealthComponent>(entity);
    EXPECT_EQ(healthComponent, nullptr);
}

TEST(Registry, ReuseEntityIDs) {
    Registry registry;
    Entity entity1 = registry.createEntity();
    registry.destroyEntity(entity1);
    Entity entity2 = registry.createEntity();
    EXPECT_EQ(entity2, entity1);
}

#endif  // REGISTRY_TEST_HPP