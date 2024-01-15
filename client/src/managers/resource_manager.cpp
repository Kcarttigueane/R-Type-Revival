#include "../../include/managers/resource_manager.hpp"

std::shared_ptr<sf::Texture> ResourceManager::loadTexture(const std::string& filename)
{
    return loadResource<sf::Texture>(_textures, filename);
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::loadSoundBuffer(const std::string& filename)
{
    return loadResource<sf::SoundBuffer>(_soundBuffers, filename);
}

std::shared_ptr<sf::Font> ResourceManager::loadFont(const std::string& filename)
{
    return loadResource<sf::Font>(_fonts, filename);
}

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
