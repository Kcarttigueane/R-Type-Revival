#if !defined(SOUND_COMPONENT_HPP)
#    define SOUND_COMPONENT_HPP

#    include <SFML/Audio.hpp>
#    include <SFML/Graphics.hpp>
#    include <SFML/System.hpp>
#    include <SFML/Window.hpp>

#    include <iostream>

struct SoundComponent {
    sf::Sound sound;

    SoundComponent(const sf::SoundBuffer& buffer) { sound.setBuffer(buffer); }

    void playSound() { sound.play(); }

    void stop() { sound.stop(); }

    void setVolumeLevel(float volume) { sound.setVolume(volume); }
};

#endif  // SOUND_COMPONENT_HPP
