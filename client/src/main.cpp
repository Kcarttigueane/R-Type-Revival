#include <SFML/Graphics.hpp>
#include "../include/managers/game_manager.hpp"

int main(void)
{
    GameManager game_manager;
    game_manager.start_game();
    game_manager.game_loop();

    return 0;
}

// #include <SFML/Graphics.hpp>
// #include "../../libs/ECS/include/ecs.hpp"

// struct SpriteComponent {
//     sf::Sprite sprite;
// };

// void MovementSystem(Registry& registry, float deltaTime)
// {
//     for (auto& entity :
//          registry.view<VelocityComponent, TransformComponent>()) {
//         auto& [vel, transform] =
//             entity.getCom<VelocityComponent, TransformComponent>();
//         transform.position += vel.velocity * deltaTime;
//     }
// }

// void RenderSystem(Registry& registry, sf::RenderWindow& window)
// {
//     for (auto& entity : registry.view<SpriteComponent, TransformComponent>()) {
//         auto& [spriteComp, transform] =
//             entity.get<SpriteComponent, TransformComponent>();
//         spriteComp.sprite.setPosition(transform.position);
//         window.draw(spriteComp.sprite);
//     }
// }

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type Revival");
//     Registry registry;
//     sf::Clock clock;

//     auto entity = registry.createEntity();
//     sf::Texture texture;
//     texture.loadFromFile("../assets/Bydos/Bydos.png");
//     registry.emplace<SpriteComponent>(entity, sf::Vector2f(100.f, 100.f));
//     auto& sprite = registry.getComponent<SpriteComponent>(entity);
//     sprite.sprite.setTexture(texture);
//     registry.addComponent<TransformComponent>(entity,
//                                               sf::Vector2f(100.f, 100.f));

//     // Entity creation
//     auto entity = registry.create();
//     registry.emplace<TransformComponent>(entity, sf::Vector2f(100.f, 100.f));
//     auto& sprite = registry.emplace<SpriteComponent>(entity);

//     while (window.isOpen()) {
//         sf::Time elapsed = clock.restart();
// float deltaTime = elapsed.asSeconds();
// sf::Event event;

// while (window.pollEvent(event)) {
//     if (event.type == sf::Event::Closed)
//         window.close();
// }

// MovementSystem(registry, deltaTime);
// window.clear();
// RenderSystem(registry, window);
// window.display();
// }

// return 0;
// }
