// #ifndef GAME_HPP_
// #define GAME_HPP_

// #include "client.hpp"
// #include "includes.hpp"

// class game {
// private:
//     int _move_left = 0;
//     int _move_right = 0;
//     int _move_up = 0;
//     int _move_down = 0;

// protected:
//     string assetsPath =
//         "/home/kc/Epitech/S5/R-TYPE/R-Type-Revival/client/assets";
//     RenderWindow _window;
//     textures _textures;
//     vector<player> _players;
//     Sprite _parallax;
//     Sprite _planet;
//     Clock _planetClock;
//     SoundBuffer _buffer;
//     Sound _sound;
//     queue<string> _messages;
//     mutex _messages_mutex;

// public:
//     game(int width, int height, const string& windowTitle);
//     string makeAnimation(
//         player& player, sf::IntRect rect, float time, int totalFrames,
//         string animation
//     );
//     void makeInfiniteAnimation(
//         Sprite& sprite, Clock& clock, sf::IntRect rect, float time,
//         int totalFrames
//     );
//     void ticUpdates();
//     Sprite& getParallax();
//     Sprite& getPlanet();
//     void resetParallax();
//     player& getLocalPlayer();
//     void makePlayerAnimation(player& player);
//     void createSound(
//         Sound& sound, SoundBuffer& soundBuffer, const string filepath
//     );
//     queue<string>& getMessages();
//     mutex& getMessagesMutex();
//     ~game();
// };

// #endif /* !GAME_HPP_ */
