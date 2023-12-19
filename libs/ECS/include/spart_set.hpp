#include "./entity.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

#if !defined(SPARSE_SET_HPP)
#define SPARSE_SET_HPP

template <typename Component> class SparseSet {
private:
  std::vector<Entity> sparse;
  std::vector<Component> dense;
  // Mapping from dense to sparse for removals
  std::vector<Entity> denseToSparse;
  size_t size = 0;

public:
  SparseSet() = default;
  ~SparseSet() = default;

  /**
   * @brief Add a component to an entity.
   *
   * @param entityId The ID of the entity to which the component is being added.
   * @param component The component being added to the entity.
   * @throws std::runtime_error If the component already exists for the entity.
   */
  void add(Entity entityId, const Component &component) {
    if (entityId >= sparse.size()) {
      sparse.resize(entityId + 1, std::numeric_limits<Entity>::max());
    }

    assert(!has(entityId) && "Component already exists for this entity.");

    sparse[entityId] = size;
    denseToSparse.push_back(entityId);
    dense.push_back(component);
    ++size;
  }

  /**
   * @brief Remove a component from an entity.
   *
   * @param entityId The ID of the entity from which the component is being
   * removed.
   * @throws std::runtime_error If the component does not exist for the entity.
   */
  void remove(Entity entityId) {
    assert(has(entityId) && "Component does not exist for this entity.");

    Entity denseIndex = sparse[entityId];
    Entity lastEntityId = denseToSparse[size - 1];

    std::swap(dense[denseIndex], dense[size - 1]);
    std::swap(denseToSparse[denseIndex], denseToSparse[size - 1]);

    sparse[lastEntityId] = denseIndex;
    sparse[entityId] = std::numeric_limits<Entity>::max();

    dense.pop_back();
    denseToSparse.pop_back();
    --size;
  }

  /**
   * @brief Get a component from an entity.
   *
   * @param entityId The ID of the entity from which the component is being
   * retrieved.
   * @return std::optional<std::reference_wrapper<const Component>> The
   * component being retrieved.
   */
  std::optional<std::reference_wrapper<const Component>>
  get(Entity entityId) const {
    if (has(entityId)) {
      return dense[sparse[entityId]];
    }
    return std::nullopt;
  }

  bool has(Entity entityId) const {
    return entityId < sparse.size() &&
           sparse[entityId] != std::numeric_limits<Entity>::max();
  }

  void clear() {
    sparse.clear();
    dense.clear();
    denseToSparse.clear();
    size = 0;
  }

  auto begin() { return dense.begin(); }

  auto begin() const { return dense.begin(); }

  auto end() { return dense.end(); }

  auto end() const { return dense.end(); }
};

#endif // SPARSE_SET_HPP
