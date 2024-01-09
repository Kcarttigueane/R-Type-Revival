#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include "../../build/common/proto/payload.pb.h"

class UDPSession {
public:
    UDPSession(
        boost::asio::io_context& io_context, boost::asio::ip::udp::socket socket
    )
        : socket_(std::move(socket)), io_context_(io_context)
    {
        std::cout << "Access" << std::endl;
        receive_payload();
    }

    ~UDPSession()
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
        socket_.send_to(
            boost::asio::buffer(&header, sizeof(header)), remote_endpoint_
        );
        socket_.send_to(
            boost::asio::buffer(serialized_payload), remote_endpoint_
        );
    }

    void start()
    {
        // Run the thread for this session
        session_thread_ = std::thread([this]() { io_context_.run(); });
    }

    uint32_t get_player_id() const { return player_id_; }

    void setId(uint32_t id) { player_id_ = id; }

    boost::asio::ip::udp::endpoint get_endpoint() const
    {
        return remote_endpoint_;
    }

    void setEndpoint(boost::asio::ip::udp::endpoint endpoint)
    {
        remote_endpoint_ = endpoint;
    }

    uint32_t getPosX() const { return posX_; }

    uint32_t getPosY() const { return posY_; }

    void setPosX(uint32_t posX) { posX_ = posX; }

    void setPosY(uint32_t posY) { posY_ = posY; }

private:
    void receive_payload()
    {
        socket_.async_receive_from(
            boost::asio::buffer(
                &current_payload_header_, sizeof(current_payload_header_)
            ),
            remote_endpoint_,
            [this](
                const boost::system::error_code& error,
                std::size_t bytes_transferred
            ) {
                if (!error) {
                    handle_receive_header(bytes_transferred);
                } else {
                    std::cerr << "Error in receive_payload header: "
                              << error.message() << std::endl;
                }
            }
        );
    }

    void handle_receive_header(std::size_t bytes_transferred)
    {
        current_payload_data_.resize(current_payload_header_.body_size());

        socket_.async_receive_from(
            boost::asio::buffer(current_payload_data_), remote_endpoint_,
            [this](
                const boost::system::error_code& error,
                std::size_t bytes_transferred
            ) {
                if (!error) {
                    handle_receive_payload(bytes_transferred);
                    receive_payload();  // Receive the next payload
                } else {
                    std::cerr
                        << "Error in receive_payload data: " << error.message()
                        << std::endl;
                }
            }
        );
    }

    void handle_receive_payload(std::size_t bytes_transferred)
    {
        process_payload();
    }

    void process_payload()
    {
        rtype::Event event;
        event.ParseFromString(current_payload_data_);
        std::cout << "Event from client "
                  << remote_endpoint_.address().to_string() << ":"
                  << remote_endpoint_.port() << ": " << event.ShortDebugString()
                  << std::endl;

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
            std::cout << "Client " << remote_endpoint_.address().to_string()
                      << ":" << remote_endpoint_.port() << " disconnected"
                      << std::endl;
        }
    }

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
};

class UDPServer {
public:
    UDPServer(boost::asio::io_context& io_context, unsigned short port)
        : socket_(
              io_context,
              boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)
          ),
          io_context_(io_context)
    {
        std::cout << "Server started on port " << port << std::endl;
        receive_payload_connect();
    }

    void send_to_all(const rtype::Payload& payload)
    {
        for (auto& client : clients) {
            client->send_payload(payload);
        }
    }

    void remove_client(UDPSession* client)
    {
        for (auto it = clients.begin(); it != clients.end(); ++it) {
            if (it->get() == client) {
                clients.erase(it);
                break;
            }
        }
    }

    void send_payload_thread()
    {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
            std::vector<rtype::Payload> payloads;
            for (auto& client : clients) {
                rtype::Payload payload;
                payload.set_identity(client->get_player_id());
                payload.set_posx(client->getPosX());
                payload.set_posy(client->getPosY());
                payload.set_width(50);
                payload.set_height(50);
                payloads.push_back(payload);
            }
            for (auto& payload : payloads) {
                send_to_all(payload);
                // std::cout << "Send payload : " << payload.ShortDebugString() << std::endl;
            }
        }
    }

    std::vector<std::unique_ptr<UDPSession>> clients;

private:
    void receive_payload_connect()
    {
        socket_.async_receive_from(
            boost::asio::buffer(
                &current_payload_header_, sizeof(current_payload_header_)
            ),
            remote_endpoint_,
            [this](
                const boost::system::error_code& error,
                std::size_t bytes_transferred
            ) {
                if (!error) {
                    current_payload_data_.resize(
                        current_payload_header_.body_size()
                    );

                    socket_.async_receive_from(
                        boost::asio::buffer(current_payload_data_),
                        remote_endpoint_,
                        [this](
                            const boost::system::error_code& error,
                            std::size_t bytes_transferred
                        ) {
                            if (!error) {
                                handle_connect_payload(bytes_transferred);
                            } else {
                                std::cerr << "Error in receive_payload data: "
                                          << error.message() << std::endl;
                            }
                        }
                    );
                } else {
                    std::cerr << "Error in receive_payload header: "
                              << error.message() << std::endl;
                }
            }
        );
    }

private:
    void handle_connect_payload(std::size_t bytes_transferred)
    {
        rtype::Connect connect;
        connect.ParseFromString(current_payload_data_);
        std::cout << "Recept Connect : " << connect.ShortDebugString()
                  << std::endl;

        // Créer un nouveau socket pour cette session
        boost::asio::ip::udp::socket session_socket(io_context_);
        session_socket.open(boost::asio::ip::udp::v4());

        // Envoyer un ID au client
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int32_t> dis(
            std::numeric_limits<int32_t>::min(),
            std::numeric_limits<int32_t>::max()
        );
        uint32_t id = dis(gen);
        rtype::ID connect_send;
        connect_send.set_id(id);
        std::string serialized_payload = connect_send.SerializeAsString();
        rtype::PayloadHeader header;
        header.set_body_size(serialized_payload.size());
        session_socket.send_to(
            boost::asio::buffer(&header, sizeof(header)), remote_endpoint_
        );
        session_socket.send_to(
            boost::asio::buffer(serialized_payload), remote_endpoint_
        );

        std::cout << "Send id : " << connect_send.ShortDebugString()
                  << std::endl;
        // Créer une nouvelle session avec le nouveau socket
        auto session = std::make_unique<UDPSession>(
            io_context_, std::move(session_socket)
        );
        session->setEndpoint(remote_endpoint_);
        session->setId(id);
        session->start();
        std::cout << "Terminate to create" << std::endl;

        // Ajouter la nouvelle session au vecteur
        clients.push_back(std::move(session));

        receive_payload_connect();
    }

    void send_payload(
        const rtype::Payload& payload,
        const boost::asio::ip::udp::endpoint& endpoint
    )
    {
        std::string serialized_payload = payload.SerializeAsString();
        rtype::PayloadHeader header;
        header.set_body_size(serialized_payload.size());
        socket_.send_to(boost::asio::buffer(&header, sizeof(header)), endpoint);
        socket_.send_to(boost::asio::buffer(serialized_payload), endpoint);
    }

    boost::asio::io_context& io_context_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    rtype::PayloadHeader current_payload_header_;
    std::string current_payload_data_;
};

int main()
{
    boost::asio::io_context io_context;
    UDPServer server(io_context, 12345);
    std::thread send_payload_thread([&server]() {
        server.send_payload_thread();
    });
    io_context.run();

    return 0;
}
