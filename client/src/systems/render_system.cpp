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
        if (sceneComponent.scene.has_value() &&
            sceneComponent.scene == _sceneManager.getCurrentScene()) {

            if (renderable.text.getFont()) {
                _window.draw(renderable.text);
            }
            if (renderable.sprite.getTexture()) {
                _window.draw(renderable.sprite);
                drawHitBox(renderable);
            }
        }
    }
}

void GameManager::drawHitBox(RenderableComponent& renderable)
{
    sf::FloatRect hitBox = renderable.sprite.getGlobalBounds();
    sf::RectangleShape hitBoxShape(sf::Vector2f(hitBox.width, hitBox.height));
    hitBoxShape.setPosition(hitBox.left, hitBox.top);
    hitBoxShape.setFillColor(sf::Color(0, 0, 0, 0));
    hitBoxShape.setOutlineColor(sf::Color::Red);
    hitBoxShape.setOutlineThickness(2.0f);
    _window.draw(hitBoxShape);
}
