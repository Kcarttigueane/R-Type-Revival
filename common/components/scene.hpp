#if !defined(SCENE_COMPONENT_HPP)
#    define SCENE_COMPONENT_HPP

#    include "../../client/include/config.hpp"

#    include <optional>

struct SceneComponent {
    std::optional<GameScenes> scene;

    // SceneComponent() : scene(std::nullopt) {}  // For entities in all sc
    SceneComponent() = default;

    explicit SceneComponent(GameScenes scene) : scene(scene) {}
};

#endif  // SCENE_COMPONENT_HPP
