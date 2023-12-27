#if !defined(SCENE_COMPONENT_HPP)
#    define SCENE_COMPONENT_HPP

#    include "../../client/include/client.hpp"

#    include <optional>

struct SceneComponent {
    std::optional<GameScenes> scene;

    SceneComponent() : scene(std::nullopt) {}  // For entities in all scenes

    explicit SceneComponent(GameScenes scene)
        : scene(scene) {}  // For specific scene
};

#endif  // SCENE_COMPONENT_HPP
