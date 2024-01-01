#include "../../include/managers/network_manager.hpp"

NetworkManager::NetworkManager(
    boost::asio::io_context& io_context, const std::string& server_ip,
    unsigned short server_port
)
    : _socket(io_context),
      _server_endpoint(boost::asio::ip::udp::endpoint(
          boost::asio::ip::address::from_string(server_ip), server_port
      ))
{
    _socket.open(boost::asio::ip::udp::v4());
    send("OK");
    start_receive();
}

void NetworkManager::send(const std::string& message)
{
    _socket.send_to(boost::asio::buffer(message), _server_endpoint);
}

void NetworkManager::start_receive()
{
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buffer), _server_endpoint,
        [this](const boost::system::error_code& error, size_t bytes_received) {
            handle_receive(error, bytes_received);
        }
    );
}

void NetworkManager::handle_receive(
    const boost::system::error_code& error, size_t bytes_received
)
{
    if (!error || error == boost::asio::error::message_size) {
        std::lock_guard<std::mutex> lock(_mutex);
        memcpy(&_payload, _recv_buffer.data(), sizeof(Payload));
    }
    start_receive();
}

void NetworkManager::stop()
{
    stop_requested_ = true;
}

Payload NetworkManager::get_payload()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _payload;
}
