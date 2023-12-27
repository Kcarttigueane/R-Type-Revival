// #include "../../include/managers/game_manager.hpp"

// void GameManager::parallaxSystem(float deltaTime)
// {
//     auto view = _registry.view<ParallaxComponent, RenderableComponent>();

//     for (auto entity : view) {
//         auto& parallax = view.get<ParallaxComponent>(entity);
//         auto& renderable = view.get<RenderableComponent>(entity);
//         auto& transform = view.get<TransformComponent>(entity);

//         transform.x -= parallax.speed /* * deltaTime */;

//         if (transform.x < -WINDOW_WIDTH) {
//             transform.x = 0.0f;
//         }

//         renderable.sprite.setPosition(sf::Vector2f(transform.x, transform.y));
//     }
// }
// //
