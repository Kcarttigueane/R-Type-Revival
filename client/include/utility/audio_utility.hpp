#if !defined(AUDIO_UTILITY_HPP)
#    define AUDIO_UTILITY_HPP

#    include <SFML/Audio.hpp>
#    include <memory>

class SoundUtility {
private:
    sf::Sound sound;

public:
    SoundUtility(const std::shared_ptr<sf::SoundBuffer>& buffer)
    {
        sound.setBuffer(*buffer);
    }

    ~SoundUtility() = default;

    void setVolume(float volume) { sound.setVolume(volume); }

    void play() { sound.play(); }
};

class MusicUtility {
private:
    sf::Music music;

public:
    MusicUtility(const std::string& filepath)
    {
        music.openFromFile(filepath);
        music.setVolume(2.5f);
    }

    ~MusicUtility() = default;

    void setVolume(float volume) { music.setVolume(volume); }

    void play() { music.play(); }
};

#endif  // AUDIO_UTILITY_HPP
