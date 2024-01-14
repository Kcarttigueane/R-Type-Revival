#include "../../include/managers/settings_manager.hpp"

SettingsManager::SettingsManager(ResourceManager& resourceManager)
    : _resourceManager(resourceManager)
{}

[[nodiscard]] int SettingsManager::getVolume() const
{
    return _volume;
}

void SettingsManager::setSettingVolume(int volume)
{
    _volume = volume;
}

[[nodiscard]] int SettingsManager::getMusic() const
{
    return _music;
}

void SettingsManager::setMusic(int music)
{
    _music = music;
}

void SettingsManager::saveSettings()
{
    // TODO: Save settings to file
}

void SettingsManager::loadSettings()
{
    // TODO: Load settings from file
}
