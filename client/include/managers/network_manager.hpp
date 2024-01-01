#if !defined(NETWORK_MANAGER_HPP)
#    define NETWORK_MANAGER_HPP

#    include <boost/array.hpp>
#    include <boost/asio.hpp>

enum class Type { PLAYER, BULLET, ENEMY, WALL, BONUS };

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

class NetworkManager {
private:
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _server_endpoint;
    boost::array<char, 128> _recv_buffer;
    Payload _payload;
    std::mutex _mutex;

public:
    NetworkManager(
        boost::asio::io_context& io_context, const std::string& server_ip,
        unsigned short server_port
    );
    ~NetworkManager() = default;

    bool stop_requested_{false};

    void send(const std::string& message);

    void start_receive();

    void handle_receive(
        const boost::system::error_code& error, std::size_t bytes_received
    );

    void stop();

    Payload get_payload();
};

#endif  // NETWORK_MANAGER_HPP
