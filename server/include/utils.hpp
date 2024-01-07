#if !defined(UTILS_HPP)
#    define UTILS_HPP

#    include <random>

#    include <iostream>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[1;35m";
const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

float getRandomFloat(float min, float max);

#endif  // UTILS_HPP
