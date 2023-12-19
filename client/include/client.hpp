#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "includes.hpp"

enum class Type {
    PLAYER,
    BULLET,
    ENEMY,
    WALL,
    BONUS
};

struct Payload {
    uint32_t idSprite;
    uint32_t id_entity;
    uint32_t posX;
    uint32_t posY;
    uint32_t width;
    uint32_t height;
};

struct Life {
    uint32_t life;
};

class ClientUDP {
public:
    bool stop_requested_{false};
    ClientUDP(boost::asio::io_context& io_context, const std::string& server_ip, unsigned short server_port);
    void send(const std::string& message);
    void start_receive();
    void handle_receive(const boost::system::error_code& error, std::size_t bytes_received);
    void stop();
    Payload get_payload();
    ~ClientUDP();

private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint server_endpoint_;
    boost::array<char, 128> recv_buffer_;
    Payload payload_;
    std::mutex mutex_;
};

#endif /* !CLIENT_HPP_ */
