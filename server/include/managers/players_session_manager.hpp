#if !defined(PLAYER_SESSION_MANAGER_HPP)
#    define PLAYER_SESSION_MANAGER_HPP

#    include <boost/array.hpp>
#    include <boost/asio.hpp>
#    include <boost/asio/io_context.hpp>
#    include <iostream>
#    include <memory>
#    include <random>
#    include <string>
#    include <thread>
#    include <vector>
#    include "../../src/proto/payload.pb.h"

class PlayerSessionManagerUDP {
private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    rtype::PayloadHeader current_payload_header_;
    std::string current_payload_data_;
    std::thread session_thread_;
    uint32_t posX_ = 200;
    uint32_t posY_ = 200;
    uint32_t width_ = 50;
    uint32_t height_ = 50;
    uint32_t player_id_ = 0;

    void receive_payload()
    {
        socket_.async_receive_from(
            boost::asio::buffer(&current_payload_header_, sizeof(current_payload_header_)),
            remote_endpoint_,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    handle_receive_header(bytes_transferred);
                } else {
                    std::cerr << "Error in receive_payload header: " << error.message()
                              << std::endl;
                }
            }
        );
    }

    void handle_receive_header(std::size_t bytes_transferred)
    {
        current_payload_data_.resize(current_payload_header_.body_size());

        socket_.async_receive_from(
            boost::asio::buffer(current_payload_data_), remote_endpoint_,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    handle_receive_payload(bytes_transferred);
                    receive_payload();  // Receive the next payload
                } else {
                    std::cerr << "Error in receive_payload data: " << error.message() << std::endl;
                }
            }
        );
    }

    void handle_receive_payload(std::size_t bytes_transferred) { process_payload(); }

    void process_payload()
    {
        rtype::Event event;
        event.ParseFromString(current_payload_data_);
        std::cout << "Event from client " << remote_endpoint_.address().to_string() << ":"
                  << remote_endpoint_.port() << ": " << event.ShortDebugString() << std::endl;

        switch (event.event()) {
            case rtype::EventType::MOVEUP:
                printf("Move up\n");
                posY_ -= 10;
                break;
            case rtype::EventType::MOVEDOWN:
                printf("Move down\n");
                posY_ += 10;
                break;
            case rtype::EventType::MOVELEFT:
                printf("Move left\n");
                posX_ -= 10;
                break;
            case rtype::EventType::MOVERIGHT:
                printf("Move right\n");
                posX_ += 10;
                break;
            default:
                break;
        }

        // Handle the received payload as needed for your game logic

        if (event.event() == rtype::EventType::QUIT) {
            std::cout << "Client " << remote_endpoint_.address().to_string() << ":"
                      << remote_endpoint_.port() << " disconnected" << std::endl;
        }
    }

public:
    PlayerSessionManagerUDP(
        boost::asio::io_context& io_context, boost::asio::ip::udp::socket socket
    )
        : socket_(std::move(socket)), io_context_(io_context)
    {
        std::cout << "Access" << std::endl;
        receive_payload();
    }

    ~PlayerSessionManagerUDP()
    {
        // Join or detach the thread before destroying the object
        if (session_thread_.joinable()) {
            session_thread_.join();
        }
        // Alternatively, you can detach the thread:
        // session_thread_.detach();
    }

    void send_payload(const rtype::Payload& payload)
    {
        std::string serialized_payload = payload.SerializeAsString();
        rtype::PayloadHeader header;
        header.set_body_size(serialized_payload.size());
        socket_.send_to(boost::asio::buffer(&header, sizeof(header)), remote_endpoint_);
        socket_.send_to(boost::asio::buffer(serialized_payload), remote_endpoint_);
    }

    void start()
    {
        // Run the thread for this session
        session_thread_ = std::thread([this]() { io_context_.run(); });
    }

    uint32_t get_player_id() const { return player_id_; }

    void setId(uint32_t id) { player_id_ = id; }

    boost::asio::ip::udp::endpoint get_endpoint() const { return remote_endpoint_; }

    void setEndpoint(boost::asio::ip::udp::endpoint endpoint) { remote_endpoint_ = endpoint; }

    uint32_t getPosX() const { return posX_; }

    uint32_t getPosY() const { return posY_; }

    void setPosX(uint32_t posX) { posX_ = posX; }

    void setPosY(uint32_t posY) { posY_ = posY; }
};

#endif  // PLAYER_SESSION_MANAGER_HPP
