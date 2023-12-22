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
  std::vector<Entity> _sparse;
  std::vector<Component> _dense;
  // Mapping from _dense to _sparse for removals
  std::vector<Entity> _denseToSparse;
  Entity size = 0;

public:
  SparseSet() = default;
  ~SparseSet() = default;

  void add(Entity entityId, const Component &component) {
    if (entityId >= _sparse.size()) {
      _sparse.resize(entityId + 1, std::numeric_limits<Entity>::max());
    }

    assert(!has(entityId) && "Component already exists for this entity.");

    _sparse[entityId] = size;
    _denseToSparse.push_back(entityId);
    _dense.push_back(component);
    ++size;
  }

  void remove(Entity entityId) {
    if (size == 0) {
      return;
    }
    assert(has(entityId) && "Component does not exist for this entity.");

    Entity denseIndex = _sparse[entityId];
    Entity lastEntityId = _denseToSparse[size - 1];

    std::swap(_dense[denseIndex], _dense[size - 1]);
    std::swap(_denseToSparse[denseIndex], _denseToSparse[size - 1]);

    _sparse[lastEntityId] = denseIndex;
    _sparse[entityId] = std::numeric_limits<Entity>::max();

    _dense.pop_back();
    _denseToSparse.pop_back();
    --size;
  }

  std::optional<std::reference_wrapper<const Component>>
  get(Entity entityId) const {
    if (has(entityId)) {
      return _dense[_sparse[entityId]];
    }
    return std::nullopt;
  }

  bool has(Entity entityId) const {
    std::cout << "entityId: " << entityId << std::endl;
    std::cout << "_sparse.size(): " << _sparse.size() << std::endl;
    return entityId < _sparse.size() &&
           _sparse[entityId] != std::numeric_limits<Entity>::max();
  }

  void clear() {
    _sparse.clear();
    _dense.clear();
    _denseToSparse.clear();
    size = 0;
  }

  auto begin() { return _dense.begin(); }

  auto begin() const { return _dense.begin(); }

  auto end() { return _dense.end(); }

  auto end() const { return _dense.end(); }

  Entity getSize() { return size; }
};

#endif // SPARSE_SET_HPP
