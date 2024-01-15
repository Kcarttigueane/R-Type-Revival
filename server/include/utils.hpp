#if !defined(UTILS_HPP)
#    define UTILS_HPP

#    include <random>

#    include <iostream>

const std::string RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";
const std::string YELLOW = "\033[1;33m";
const std::string BLUE = "\033[1;34m";
const std::string MAGENTA = "\033[1;35m";
const std::string CYAN = "\033[1;36m";

const std::string RESET = "\033[0m";

float getRandomFloat(float min, float max);

std::pair<double, double> getDirection(float x1, float y1, float x2, float y2);

#endif  // UTILS_HPP
