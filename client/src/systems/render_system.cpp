#include "../../include/managers/game_manager.hpp"

void GameManager::renderSystem()
{
    auto view = _registry.view<RenderableComponent, SceneComponent>();
    for (auto entity : view) {
        auto& sceneComponent = view.get<SceneComponent>(entity);
        if (!sceneComponent.scene.has_value()) {
            auto& renderable = view.get<RenderableComponent>(entity);
            _window.draw(renderable.sprite);
        }
    }
    for (auto entity : view) {
        auto& renderable = view.get<RenderableComponent>(entity);
        auto& sceneComponent = view.get<SceneComponent>(entity);
        if (_registry.all_of<TransformComponent>(entity)) {
            auto& transform = _registry.get<TransformComponent>(entity);
            renderable.sprite.setPosition(sf::Vector2f(transform.x, transform.y)
            );
        }

        if (sceneComponent.scene.has_value() &&
            sceneComponent.scene == _sceneManager.getCurrentScene()) {

            if (renderable.text.getFont()) {
                _window.draw(renderable.text);
            }
            if (renderable.sprite.getTexture()) {
                _window.draw(renderable.sprite);
                // sf::FloatRect hitbox = renderable.sprite.getGlobalBounds();
                // sf::RectangleShape hitboxShape(
                //     sf::Vector2f(hitbox.width, hitbox.height)
                // );
                // hitboxShape.setPosition(hitbox.left, hitbox.top);
                // hitboxShape.setFillColor(sf::Color(0, 0, 0, 0));
                // hitboxShape.setOutlineColor(sf::Color::Red);
                // hitboxShape.setOutlineThickness(2.0f);
                // _window.draw(hitboxShape);
            }
        }
    }
}
