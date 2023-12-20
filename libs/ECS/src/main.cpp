#include "../include/logger.hpp"
#include "../include/registry.hpp"
#include "../include/spart_set.hpp"
#include "./components/health.hpp"

int main(void) {
  // SparseSet<HealthComponent> healthComponentsStorage;

  // Entity entity1 = 1;

  // HealthComponent healthComponent1 = {100, 0.5f, 0.0f};

  // healthComponentsStorage.add(entity1, healthComponent1);

  // Entity entity2 = 2;

  // HealthComponent healthComponent2 = {100, 0.5f, 0.0f};

  // healthComponentsStorage.add(entity2, healthComponent2);

  // for (auto &healthComponent : healthComponentsStorage) {
  //   std::cout << healthComponent.healthPoints << std::endl;
  // }
  // logger.log(Logger::Level::INFO, "This is an info message.");
  // logger.log(Logger::Level::WARNING, "This is a warning message.");
  // logger.log(Logger::Level::ERROR, "This is an error message.");

  Registry registry;
  auto entity = registry.createEntity();
  HealthComponent healthComponent = {100, 0.5f, 0.0f};
  registry.emplace<HealthComponent>(entity, healthComponent);

  auto *position = registry.getComponent<HealthComponent>(entity);

  // if (position) {
  //   std::cout << position->healthPoints << std::endl;
  // }

  // registry.removeComponent<HealthComponent>(entity);
  // registry.destroyEntity(entity);

  //  spdlog::info("Welcome to spdlog!");
  // spdlog::error("Some error message with arg: {}", 1);

  // spdlog::warn("Easy padding in numbers like {:08d}", 12);
  // spdlog::critical(
  //     "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  // spdlog::info("Support for floats {:03.2f}", 1.23456);
  // spdlog::info("Positional args are {1} {0}..", "too", "supported");
  // spdlog::info("{:<30}", "left aligned");

  // spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  // spdlog::debug("This message should be displayed..");

  // // change log pattern
  // spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

  // // Compile time log levels
  // // define SPDLOG_ACTIVE_LEVEL to desired level
  // SPDLOG_TRACE("Some trace message with param {}", 42);
  // SPDLOG_DEBUG("Some debug message");
  return 0;
}
