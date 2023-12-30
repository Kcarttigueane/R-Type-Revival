#if !defined(RESOURCE_MANAGER_HPP)
#    define RESOURCE_MANAGER_HPP

#    include <SFML/Audio.hpp>
#    include <SFML/Graphics.hpp>
#    include <iostream>
#    include <map>
#    include <memory>
#    include <stdexcept>
#    include <string>

class ResourceManager {
private:
    std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> _soundBuffers;
    std::map<std::string, std::shared_ptr<sf::Music>> _music;
    std::map<std::string, std::shared_ptr<sf::Font>> _fonts;

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    std::shared_ptr<sf::Texture> loadTexture(const std::string& filename)
    {
        return loadResource<sf::Texture>(_textures, filename);
    }

    std::shared_ptr<sf::SoundBuffer> loadSoundBuffer(const std::string& filename
    )
    {
        return loadResource<sf::SoundBuffer>(_soundBuffers, filename);
    }

    std::shared_ptr<sf::Font> loadFont(const std::string& filename)
    {
        return loadResource<sf::Font>(_fonts, filename);
    }

private:
    template <typename ResourceType, typename ResourceMap>
    std::shared_ptr<ResourceType> loadResource(
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
                throw std::runtime_error(
                    "Failed to load resource: " + filename
                );
            }
        }
    }
};

#endif  // RESOURCE_MANAGER_HPP
