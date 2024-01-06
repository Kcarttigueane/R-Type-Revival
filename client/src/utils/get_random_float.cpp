#include "../../include/utils.hpp"

/**
     * \brief Generates a random float within a range.
     * \param min Minimum value of the range.
     * \param max Maximum value of the range.
     * \return Randomly generated float.
     */
float getRandomFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}
