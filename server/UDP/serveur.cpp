#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <thread>
#include <random>
#include <string>
#include "payload.pb.h"

class UDPServer {
public:
    UDPServer(boost::asio::io_context& io_context, unsigned short port)
        : socket_(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
          payload_thread_([this]() { send_payload_thread(); }) {
        std::cout << "Server started on port " << port << std::endl;
        receive_payload();
    }

    ~UDPServer() {
        payload_thread_.join();
    }

private:
    void receive_payload() {
        socket_.async_receive_from(
            boost::asio::buffer(&current_payload_header_, sizeof(current_payload_header_)),
            remote_endpoint_,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    // Add the client to the list of clients if it is not already in it
                    if (std::find(clients.begin(), clients.end(), remote_endpoint_) == clients.end())
                        clients.push_back(remote_endpoint_);
                    handle_receive_header(bytes_transferred);
                } else {
                    std::cerr << "Error in receive_payload header: " << error.message() << std::endl;
                }
            });
    }

    void handle_receive_header(std::size_t bytes_transferred) {
        std::cout << "Received payload header. Bytes Transferred: " << current_payload_header_.body_size()<< std::endl;

        current_payload_data_.resize(current_payload_header_.body_size());

        socket_.async_receive_from(
            boost::asio::buffer(current_payload_data_),
            remote_endpoint_,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    handle_receive_payload(bytes_transferred);
                    receive_payload();  // Receive the next payload
                } else {
                    std::cerr << "Error in receive_payload data: " << error.message() << std::endl;
                }
            });
    }

    void handle_receive_payload(std::size_t bytes_transferred) {
        process_payload();
    }

    void process_payload() {
        rtype::Event event;
        event.ParseFromString(current_payload_data_);
        std::cout << "Event : " << event.ShortDebugString() << std::endl;
        if (event.event() == rtype::EventType::QUIT) {
            std::cout << "Client " << remote_endpoint_.address().to_string() << ":" << remote_endpoint_.port() << " disconnected" << std::endl;
            clients.erase(std::remove(clients.begin(), clients.end(), remote_endpoint_), clients.end());
        }
    }

    void send_payload_thread() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            rtype::Payload payload;
            payload.set_idsprite(static_cast<uint32_t>(rtype::Type::PLAYER));
            payload.set_posx(posX_);
            payload.set_posy(posY_);
            payload.set_width(200);
            payload.set_height(250);
            if (!clients.empty()) {
                for (const auto& client : clients) {
                    send_payload(payload, client);
                }
            }
        }
    }

    void send_payload(const rtype::Payload& payload, const boost::asio::ip::udp::endpoint& endpoint) {
        std::string serialized_payload = payload.SerializeAsString();
        rtype::PayloadHeader header;
        header.set_body_size(serialized_payload.size());
        std::cout << "Sending payload header. Body Size: " << header.body_size() << std::endl;
        socket_.send_to(boost::asio::buffer(&header, sizeof(header)), endpoint);
        socket_.send_to(boost::asio::buffer(serialized_payload), endpoint);
    }

    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    std::vector<boost::asio::ip::udp::endpoint> clients;
    std::thread payload_thread_;
    uint32_t posX_ = 300;
    uint32_t posY_ = 200;
    rtype::PayloadHeader current_payload_header_;
    std::string current_payload_data_;
};

int main() {
    boost::asio::io_context io_context;
    UDPServer server(io_context, 12345);

    io_context.run();

    return 0;
}
