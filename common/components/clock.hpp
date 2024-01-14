
#ifndef ECS_CLOCK_COMPONENT_HPP
#define ECS_CLOCK_COMPONENT_HPP

#include <chrono>

struct ClockComponent {
    float timeout;
    std::chrono::_V2::steady_clock::time_point lastUpdate;
};

#endif // ECS_CLOCK_COMPONENT_HPP