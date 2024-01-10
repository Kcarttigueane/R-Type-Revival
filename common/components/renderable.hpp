#ifndef ECS_RENDERABLE_COMPONENT_HPP
#define ECS_RENDERABLE_COMPONENT_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <memory>

struct RenderableComponent {
    std::shared_ptr<sf::Texture> texture;
    sf::Text text;
    sf::Sprite sprite;
    sf::IntRect frameRect;
    std::shared_ptr<sf::Shape> shape;
};

#endif  // ECS_RENDERABLE_COMPONENT_HPP
