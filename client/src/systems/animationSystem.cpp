#include "../../include/managers/game_manager.hpp"

void GameManager::makeAllAnimations() {
    auto view = _registry.view<RenderableComponent>();
    for (auto entity : view) {
        if (_registry.all_of<HoldAnimationComponent>(entity)) {
            sf::IntRect rectangle = view.get<RenderableComponent>(entity).frameRect;
            makeHoldAnimation(entity, rectangle);
        }
        else if (_registry.all_of<SingleAnimationComponent>(entity)) {
            sf::IntRect rectangle = view.get<RenderableComponent>(entity).frameRect;
            makeSingleAnimation(entity, rectangle);
        }
        else if (_registry.all_of<InfiniteAnimationComponent>(entity)) {
            sf::IntRect rectangle = view.get<RenderableComponent>(entity).frameRect;
            makeInfiniteAnimation(entity, rectangle);
        }
    }
}

void GameManager::makeHoldAnimation(entt::entity& entity, sf::IntRect rectangle) {
    auto& entityRenderable = _registry.get<RenderableComponent>(entity);
    auto& entityAnimation = _registry.get<HoldAnimationComponent>(entity);

    if (entityAnimation.status) {
        float frameTime = entityAnimation.animationTime / entityAnimation.totalFrames;
        float elapsedTime = entityAnimation.animationClock.getElapsedTime().asSeconds();
        int currentFrame = static_cast<int>((elapsedTime / frameTime)) % entityAnimation.totalFrames;
        entityRenderable.sprite.setTextureRect(sf::IntRect(rectangle.left + currentFrame * rectangle.width, rectangle.top, rectangle.width, rectangle.height));

        if (currentFrame >= entityAnimation.totalFrames - 1) {  
            entityAnimation.animationClock.restart();
            entityAnimation.status = false;
        }
    }
}


void GameManager::makeSingleAnimation(entt::entity& entity, sf::IntRect rectangle) {
    auto& entityRenderable = _registry.get<RenderableComponent>(entity);
    auto& entityAnimation = _registry.get<SingleAnimationComponent>(entity);
    float frameTime = entityAnimation.animationTime / entityAnimation.totalFrames;
    float elapsedTime = entityAnimation.animationClock.getElapsedTime().asSeconds();
    int currentFrame = static_cast<int>((elapsedTime / frameTime)) % entityAnimation.totalFrames;
    sf::IntRect newRectangle = sf::IntRect(rectangle.left + currentFrame * rectangle.width, rectangle.top, rectangle.width, rectangle.height);
    entityRenderable.sprite.setTextureRect(newRectangle);
    entityRenderable.frameRect = newRectangle;
    if (currentFrame == entityAnimation.totalFrames) {
        _registry.destroy(entity);
    }
}

void GameManager::makeInfiniteAnimation(entt::entity& entity, sf::IntRect rectangle) {
    auto& entityRenderable = _registry.get<RenderableComponent>(entity);
    auto& entityAnimation = _registry.get<InfiniteAnimationComponent>(entity);
    float frameTime = entityAnimation.animationTime / entityAnimation.totalFrames;
    float elapsedTime = entityAnimation.animationClock.getElapsedTime().asSeconds();
    int currentFrame = static_cast<int>((elapsedTime / frameTime)) % entityAnimation.totalFrames;
    sf::IntRect newRectangle = sf::IntRect(rectangle.left + currentFrame * rectangle.width, rectangle.top, rectangle.width, rectangle.height);
    entityRenderable.sprite.setTextureRect(newRectangle);
    entityRenderable.frameRect = newRectangle;
    if (currentFrame == entityAnimation.totalFrames) {
        entityAnimation.animationClock.restart();
    }
}