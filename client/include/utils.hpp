#if !defined(UTILS_HPP)
#    define UTILS_HPP

#    include <random>
#    include <cmath>

float getRandomFloat(float min, float max);

std::pair<double, double> get_direction(float x1, float y1, float x2, float y2);

#endif  // UTILS_HPP
