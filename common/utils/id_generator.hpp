#if !defined(ID_GENERATOR_HPP)
#    define ID_GENERATOR_HPP

#    include <cstdint>
#    include <limits>
#    include <random>
#    include <set>
#    include <stdexcept>

class IdGenerator {
private:
    std::set<uint32_t> usedIds;
    std::mt19937 gen;  // Mersenne Twister engine

    /**
     * \brief Generates a random uint32_t value.
     * \param min Minimum value of the range.
     * \param max Maximum value of the range.
     * \return Randomly generated uint32_t.
     */
    uint32_t getRandomID(uint32_t min, uint32_t max)
    {
        std::uniform_int_distribution<uint32_t> distribution(min, max);
        return distribution(gen);
    }

public:
    IdGenerator() : gen(std::random_device()()) {}

    uint32_t generateId()
    {
        uint32_t id = getRandomID(1, std::numeric_limits<uint32_t>::max() - 1);

        while (usedIds.find(id) != usedIds.end()) {
            id = getRandomID(1, std::numeric_limits<uint32_t>::max() - 1);
        }

        usedIds.insert(id);
        return id;
    }

    void releaseId(uint32_t id) { usedIds.erase(id); }
};

#endif  // ID_GENERATOR_HPP
