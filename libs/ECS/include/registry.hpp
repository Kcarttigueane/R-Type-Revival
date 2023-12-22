
#if !defined(REGISTRY_HPP)
#define REGISTRY_HPP

#include "../include/spart_set.hpp"
#include "../src/components/health.hpp"
#include "./entity.hpp"
#include "./logger.hpp"
#include <vector>

#include <memory>
#include <typeindex>
#include <unordered_map>

class Registry {
private:
  Logger _logger;
  Entity _nextEntityId = 0;
  std::vector<Entity> _freeIds;

  struct IComponentSet {
    virtual ~IComponentSet() = default;
    virtual void removeEntity(Entity entity) = 0;
  };

  template <typename Component>
  struct ComponentSet : SparseSet<Component>, IComponentSet {
    void removeEntity(Entity entity) override {
      std::cout << "Removing entity: " << entity << std::endl;
      this->remove(entity);
    };
  };

  std::unordered_map<std::type_index, std::unique_ptr<IComponentSet>>
      _componentSets;

public:
  Entity createEntity() {
    if (!_freeIds.empty()) {
      Entity id = _freeIds.back();
      _freeIds.pop_back();
      std::cout << "Reusing entity with ID: " << id << std::endl;
      return id;
    }
    std::cout << "Creating entity with ID: " << _nextEntityId << std::endl;
    return _nextEntityId++;
  }

  void destroyEntity(Entity entity) {
    _logger.log(Logger::Level::INFO,
                "Destroying entity: " + std::to_string(entity));
    if (std::find(_freeIds.begin(), _freeIds.end(), entity) != _freeIds.end()) {
      _logger.log(Logger::Level::INFO,
                  "Warning: Attempted to destroy already destroyed entity: " +
                      std::to_string(entity));
      return;
    }

    for (auto &[type, set] : _componentSets) {
      try {
        std::cout << "set: " << set.get() << std::endl;
        set->removeEntity(entity);
      } catch (const std::runtime_error &e) {
        _logger.log(Logger::Level::INFO, "Info: " + std::string(e.what()));
      }
    }
    _freeIds.push_back(entity);
  }

  template <typename Component, typename... Args>
  void emplace(Entity entity, Args &&...args) {
    getComponentSet<Component>().add(entity,
                                     Component(std::forward<Args>(args)...));
  }

  template <typename Component> Component *getComponent(Entity entity) {
    auto componentOpt = getComponentSet<Component>().get(entity);
    return componentOpt ? &const_cast<Component &>(componentOpt->get())
                        : nullptr;
  }

  template <typename Component>
  const Component *getComponent(Entity entity) const {
    auto componentOpt = getComponentSet<Component>().get(entity);
    return componentOpt ? &componentOpt->get() : nullptr;
  }

  template <typename Component> void removeComponent(Entity entity) {
    getComponentSet<Component>().remove(entity);
  }

private:
  template <typename Component> ComponentSet<Component> &getComponentSet() {
    std::type_index typeIndex(typeid(Component));
    std::cout << typeIndex.name() << std::endl;

    if (_componentSets.find(typeIndex) == _componentSets.end()) {
      _componentSets[typeIndex] = std::make_unique<ComponentSet<Component>>();
    }

    return *static_cast<ComponentSet<Component> *>(
        _componentSets[typeIndex].get());
  }
};

#endif // REGISTRY_HPP
