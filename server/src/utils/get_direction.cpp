#include "../../include/utils.hpp"

std::pair<double, double> getDirection(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance != 0) {
        dx /= distance;
        dy /= distance;
    }
    return std::make_pair(dx, dy);
}