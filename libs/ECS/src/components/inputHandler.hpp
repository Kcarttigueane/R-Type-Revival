
#ifndef ECS_INPUT_COMPONENT_HPP
#define ECS_INPUT_COMPONENT_HPP

#include <map>
#include <string>
#include <functional>

struct InputComponent {
  std::map<std::string, std::function<void()>> actionBindings;
};

#endif // ECS_INPUT_COMPONENT_HPP
