#ifndef GAME_HPP_
#define GAME_HPP_

#include "includes.hpp"
#include "client.hpp"
#include "textures.hpp"
#include "player.hpp"
#include "menu.hpp"

class game {
private:
    int _move_left = 0;
    int _move_right = 0;
    int _move_up = 0;
    int _move_down = 0;
protected:
    RenderWindow _window;
    textures _textures;
    vector<player> _players;
    Sprite _parallax;
    Sprite _planet;
    Clock _planetClock;
    SoundBuffer _buffer;
    Sound _sound;
    queue<string> _messages;
    mutex _messages_mutex;
    Menu _menu;

  public:
    game(int width, int height, const string &windowTitle);
    string makeAnimation(player &player, int left, int top, int width, int height, float time, int totalFrames, string animation);
    void makeInfiniteAnimation(Sprite &sprite, Clock &clock, int left, int top, int width, int height, float time, int totalFrames);
    void windowLoop(ClientUDP &client);
    void ticUpdates();
    void displayUpdates();
    void initParallax(textures &textures);
    Sprite &getParallax();
    Sprite &getPlanet();
    void resetParallax();
    void moveParallax();
    void moveLocalPlayer();
    void closeWindow(Event &event);
    void checkEvents(Event &event);
    player &getLocalPlayer();
    void checkMovementKeyPress(Event &event);
    void checkMovementKeyRelease(Event &event);
    void makePlayerAnimation(player &player);
    void createSound(Sound &sound, SoundBuffer &soundBuffer, const string filepath);
    queue<string> &getMessages();
    mutex &getMessagesMutex();
    ~game();
};

#endif /* !GAME_HPP_ */
