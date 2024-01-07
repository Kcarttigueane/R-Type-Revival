#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include "payload.pb.h"  // Inclure les fichiers générés par protobuf

class ClientUDP {
public:
    bool stop_requested_{false};

    ClientUDP(
        boost::asio::io_context& io_context, const std::string& server_ip,
        unsigned short server_port
    )
        : socket_(io_context),
          server_endpoint_(boost::asio::ip::udp::endpoint(
              boost::asio::ip::address::from_string(server_ip), server_port
          ))
    {
        socket_.open(boost::asio::ip::udp::v4());
        IdEntity_ = 0;
        rtype::Connect connect;
        connect.set_message("OK");
        std::string serialized_payload = connect.SerializeAsString();
        rtype::PayloadHeader header;
        header.set_body_size(serialized_payload.size());

        // Send the header containing the size
        socket_.async_send_to(
            boost::asio::buffer(&header, sizeof(header)), server_endpoint_,
            [](const boost::system::error_code&, std::size_t) {}
        );

        // Send the serialized payload
        socket_.async_send_to(
            boost::asio::buffer(serialized_payload), server_endpoint_,
            [](const boost::system::error_code&, std::size_t) {}
        );
        receive_connect();
    }

    void receive_connect()
    {
        socket_.async_receive_from(
            boost::asio::buffer(&current_payload_header_, sizeof(current_payload_header_)),
            server_endpoint_,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {

                    current_payload_data_.resize(current_payload_header_.body_size());

                    socket_.async_receive_from(
                        boost::asio::buffer(current_payload_data_), server_endpoint_,
                        [this](
                            const boost::system::error_code& error, std::size_t bytes_transferred
                        ) {
                            if (!error) {
                                rtype::ID message;
                                message.ParseFromString(current_payload_data_);
                                std::cout << "Message : " << message.ShortDebugString()
                                          << std::endl;
                                IdEntity_ = message.id();
                                if (IdEntity_ != 0)
                                    receive_payload();
                            } else {
                                std::cerr << "Error in receive_payload data: " << error.message()
                                          << std::endl;
                            }
                        }
                    );
                } else {
                    std::cerr << "Error in receive_payload header: " << error.message()
                              << std::endl;
                }
            }
        );
    }

    void receive_payload()
    {
        socket_.async_receive_from(
            boost::asio::buffer(&current_payload_header_, sizeof(current_payload_header_)),
            server_endpoint_,
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
            boost::asio::buffer(current_payload_data_), server_endpoint_,
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
        if (frameIndex_ == 11)
            frameIndex_ = 0;
        else
            frameIndex_++;
        rtype::Payload payload;
        payload.ParseFromString(current_payload_data_);
        payload_ = payload;
        if (payloads_.size() == 0) {
            payloads_.push_back(payload);
            std::cout << "First payload " << payload.ShortDebugString() << std::endl;
        } else {
            bool exist = false;
            for (auto it = payloads_.begin(); it != payloads_.end(); it++) {
                if (it->identity() == payload.identity()) {
                    *it = payload;
                    exist = true;
                }
            }
            if (!exist)
                payloads_.push_back(payload);
        }
    }

    void stop() { stop_requested_ = true; }

    int getFrameIndex() { return frameIndex_; }

    uint32_t getIdEntity() { return IdEntity_; }

    void setIdEntity(uint32_t id) { IdEntity_ = id; }

    void setFrameIndex(int frameIndex) { frameIndex_ = frameIndex; }

    rtype::Payload get_payload()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return payload_;
    }

    std::vector<rtype::Payload> get_payloads()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return payloads_;
    }

    void send_payload(const rtype::Event& event)
    {
        std::string serialized_payload = event.SerializeAsString();
        rtype::PayloadHeader header;
        header.set_body_size(serialized_payload.size());
        // Send the header containing the size
        socket_.async_send_to(
            boost::asio::buffer(&header, sizeof(header)), server_endpoint_,
            [](const boost::system::error_code&, std::size_t) {}
        );

        // Send the serialized payload
        socket_.async_send_to(
            boost::asio::buffer(serialized_payload), server_endpoint_,
            [](const boost::system::error_code&, std::size_t) {}
        );
        std::cout << "Send payload : " << event.ShortDebugString() << std::endl;
    }

private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint server_endpoint_;
    boost::array<char, 128> recv_buffer_;
    rtype::Payload payload_;
    std::vector<rtype::Payload> payloads_;
    std::mutex mutex_;
    int frameIndex_;
    rtype::PayloadHeader current_payload_header_;
    std::string current_payload_data_;
    uint32_t IdEntity_;
};

rtype::Event handle_key(sf::Keyboard::Key key)
{
    rtype::Event event;
    switch (key) {
        case sf::Keyboard::Up:
            event.set_event(rtype::EventType::MOVEUP);
            break;
        case sf::Keyboard::Down:
            event.set_event(rtype::EventType::MOVEDOWN);
            break;
        case sf::Keyboard::Left:
            event.set_event(rtype::EventType::MOVELEFT);
            break;
        case sf::Keyboard::Right:
            event.set_event(rtype::EventType::MOVERIGHT);
            break;
        case sf::Keyboard::Space:
            event.set_event(rtype::EventType::SHOOT);
            break;
        default:
            break;
    }
    return event;
}

int main()
{
    boost::asio::io_context io_context;
    ClientUDP client(io_context, "127.0.0.1", 1234);

    std::queue<rtype::Event> messages;
    std::mutex messages_mutex;

    std::thread client_thread([&io_context, &client, &messages, &messages_mutex]() {
        while (true) {
            io_context.poll();  // Handle asynchronous operations

            // Check for stop request
            if (client.stop_requested_) {
                std::cout << "Stopping client thread..." << std::endl;
                rtype::Event event;
                event.set_event(rtype::EventType::QUIT);
                client.send_payload(event);
                break;
            }

            // Send messages to the server
            {
                std::lock_guard<std::mutex> lock(messages_mutex);
                while (!messages.empty()) {
                    client.send_payload(messages.front());
                    messages.pop();
                }
            }
        }
    });

    sf::RenderWindow window(sf::VideoMode(800, 600), "Animation avec SFML");

    sf::Texture texture;
    if (!texture.loadFromFile("new.png")) {
        // Gérer l'erreur si la texture ne peut pas être chargée
        return -1;
    };

    // Découper la sprite sheet en frames
    std::vector<sf::Sprite> frames;
    const int frameWidth = 205 / 12;  // Largeur d'une frame en pixels
    const int frameHeight = 18;       // Hauteur d'une frame en pixels
    for (int y = 0; y < texture.getSize().y - 1; y += frameHeight) {
        for (int x = 0; x < texture.getSize().x - 1; x += frameWidth) {
            sf::IntRect frameRect(x, y, frameWidth, frameHeight);
            sf::Sprite frame(texture, frameRect);
            frames.push_back(frame);
        }
        frames.pop_back();  // La dernière frame est vide, on la supprime
    }

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Close the window
            }

            // Handle other events and add messages to the queue
            if (event.type == sf::Event::KeyPressed) {
                // Example: Send a message when a key is pressed
                std::lock_guard<std::mutex> lock(messages_mutex);
                messages.push(handle_key(event.key.code));
            }
        }

        window.clear(sf::Color::Black);

        auto payloads = client.get_payloads();
        // for (auto payload : payloads) {
        //     std::cout << "Payload : " << payload.ShortDebugString() << std::endl;
        // }
        window.draw(frames[client.getFrameIndex()]);

        window.display();
    }

    // Signal the client thread to stop
    client.stop();
    client_thread.join();  // Wait for the client thread to finish

    return 0;
}
