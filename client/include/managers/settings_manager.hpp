#if !defined(SETTINGS_MANAGER_HPP)
#    define SETTINGS_MANAGER_HPP

#    include "resource_manager.hpp"

/**
 * \class SettingsManager
 * \brief Manages game settings like volume and music levels.
 *
 * This class is responsible for handling the settings of the game,
 * including volume and music. It interacts with the ResourceManager
 * to manage these settings.
 */
class SettingsManager {
private:
    int _volume = 50;
    int _music = 50;
    ResourceManager& _resourceManager;
    // TODO: See with dylan and tom about the settings

public:
    SettingsManager() = delete;

    SettingsManager(ResourceManager& resourceManager)
        : _resourceManager(resourceManager)
    {}

    ~SettingsManager(
        // TODO: Call function to save settings to file
    ) = default;

    [[nodiscard]] int getVolume() const { return _volume; }

    void setSettingVolume(int volume) { _volume = volume; }

    [[nodiscard]] int getMusic() const { return _music; }

    void setMusic(int music) { _music = music; }

    void saveSettings()
    {
        // TODO: Save settings to file
    }

    void loadSettings()
    {
        // TODO: Load settings from file
    }
};

#endif  // SETTINGS_MANAGER_HPP
