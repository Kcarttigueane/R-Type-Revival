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

public:
    SettingsManager() = delete;

    SettingsManager(ResourceManager& resourceManager) : _resourceManager(resourceManager) {}

    ~SettingsManager(
        // TODO: Call function to save settings to file
    ) = default;

    [[nodiscard]] int getVolume() const;

    void setSettingVolume(int volume);

    [[nodiscard]] int getMusic() const;

    void setMusic(int music);

    void saveSettings();

    void loadSettings();
};

#endif  // SETTINGS_MANAGER_HPP
