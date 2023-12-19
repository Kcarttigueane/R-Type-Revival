#include "../include/game.hpp"

queue<string> &game::getMessages() {
    return _messages;
};

mutex &game::getMessagesMutex() {
    return _messages_mutex;
}

game::game(int width, int height, const std::string &windowTitle) : _window(VideoMode(width, height), windowTitle), _textures(assetsPath) {
    cout << "Window created with size {" << width << ", " << height << "}." << endl;
    boost::asio::io_context io_context;
    ClientUDP client(io_context, "127.0.0.1", 12345);
        std::thread client_thread([this, &io_context, &client]() {
        while (true) {
            io_context.poll();
            if (client.stop_requested_) {
                std::cout << "Stopping client thread..." << std::endl;
                client.send("QUIT");
                break;
            } else {
                std::lock_guard<std::mutex> lock(getMessagesMutex());
                while (!getMessages().empty()) {
                    client.send(getMessages().front());
                    std::cout << "Sending message: " << getMessages().front() << std::endl;
                    getMessages().pop();
                }
            }
        }
    });
    initParallax(_textures);
    _players.push_back(player(1, "local", _textures.getShipsTexture()));
    createSound(_sound, _buffer, assetsPath + "/SoundFX/shot2.wav");
    windowLoop(client);
    client.stop();
    client_thread.join();
}


void game::ticUpdates() {
    resetParallax();
    moveParallax();
    moveLocalPlayer();
}

void game::makePlayerAnimation(player &player) {
    string playerAnimation = player.getAnimation();
    if (playerAnimation == "down") {
        player.setAnimation(makeAnimation(player, 66, 0, 33, 17, 0.3f, -3, "down"));
    } if (playerAnimation == "up") {
        player.setAnimation(makeAnimation(player, 66, 0, 33, 17, 0.3f, 3, "up"));
    } if (playerAnimation == "static") {
        player.getSprite().setTextureRect(IntRect(66, 0, 33, 17));
    }
}

game::~game() {}
