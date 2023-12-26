#include "../include/game.hpp"

void game::createSound(
    Sound& sound, SoundBuffer& soundBuffer, const string filepath
)
{
    soundBuffer.loadFromFile(filepath);
    sound.setBuffer(soundBuffer);
    sound.setVolume(2.5f);
}
