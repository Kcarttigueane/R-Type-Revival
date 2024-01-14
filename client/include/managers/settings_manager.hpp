#if !defined(SETTINGS_MANAGER_HPP)
#    define SETTINGS_MANAGER_HPP

#    include "resource_manager.hpp"

/**
 * @file settings_manager.hpp
 * @brief File containing the SettingsManager class.
 */

/**
 * @class SettingsManager
 * @brief Manages game settings like volume and music levels.
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
    /**
     * @brief Deleted default constructor.
     */
    SettingsManager() = delete;

    /**
     * @brief Constructs a new SettingsManager object.
     * @param resourceManager Reference to the ResourceManager.
     */
    SettingsManager(ResourceManager& resourceManager);

    /**
     * @brief Default destructor.
     */
    ~SettingsManager() = default;

    /**
     * @brief Gets the volume setting.
     * @return The volume setting.
     */
    [[nodiscard]] int getVolume() const;

    /**
     * @brief Sets the volume setting.
     * @param volume The new volume setting.
     */
    void setSettingVolume(int volume);

    /**
     * @brief Gets the music setting.
     * @return The music setting.
     */
    [[nodiscard]] int getMusic() const;

    /**
     * @brief Sets the music setting.
     * @param music The new music setting.
     */
    void setMusic(int music);

    /**
     * @brief Saves the settings to a file.
     */
    void saveSettings();

    /**
     * @brief Loads the settings from a file.
     */
    void loadSettings();
};

#endif  // SETTINGS_MANAGER_HPP
