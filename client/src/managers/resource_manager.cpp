#include "../../include/managers/resource_manager.hpp"

/**
     * \brief Loads a texture resource from a file.
     * \param filename Path to the texture file.
     * \return Shared pointer to the loaded texture.
     */
std::shared_ptr<sf::Texture> ResourceManager::loadTexture(
    const std::string& filename
)
{
    return loadResource<sf::Texture>(_textures, filename);
}

/**
     * \brief Loads a sound buffer resource from a file.
     * \param filename Path to the sound buffer file.
     * \return Shared pointer to the loaded sound buffer.
     */
std::shared_ptr<sf::SoundBuffer> ResourceManager::loadSoundBuffer(
    const std::string& filename
)
{
    return loadResource<sf::SoundBuffer>(_soundBuffers, filename);
}

/**
     * \brief Loads a font resource from a file.
     * \param filename Path to the font file.
     * \return Shared pointer to the loaded font.
     */
std::shared_ptr<sf::Font> ResourceManager::loadFont(const std::string& filename)
{
    return loadResource<sf::Font>(_fonts, filename);
}

/**
     * \brief Generic function to load a resource.
     * \param resourceMap Reference to the map storing the resource type.
     * \param filename Path to the resource file.
     * \return Shared pointer to the loaded resource.
     */
template <typename ResourceType, typename ResourceMap>
std::shared_ptr<ResourceType> ResourceManager::loadResource(
    ResourceMap& resourceMap, const std::string& filename
)
{
    auto iter = resourceMap.find(filename);
    if (iter != resourceMap.end()) {
        return iter->second;
    } else {
        auto resource = std::make_shared<ResourceType>();
        // TODO : music should be openFromFile

        if (resource->loadFromFile(filename)) {
            std::cout << "Loading resource: " << filename << std::endl;
            resourceMap[filename] = resource;
            return resource;
        } else {
            throw std::runtime_error("Failed to load resource: " + filename);
        }
    }
}
