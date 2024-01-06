#include "../../include/utils.hpp"

/**
     * \brief Generates a random float within a range.
     * \param min Minimum value of the range.
     * \param max Maximum value of the range.
     * \return Randomly generated float.
     */
float getRandomID(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> distribution(
        std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()
    );
    return distribution(gen);
}
