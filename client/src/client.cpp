#include "../include/game.hpp"

ClientUDP::ClientUDP(asio::io_context& io_context, const string& server_ip, unsigned short server_port)
    : socket_(io_context), server_endpoint_(boost::asio::ip::udp::endpoint(asio::ip::address::from_string(server_ip), server_port)) {
    socket_.open(asio::ip::udp::v4());
    send("OK");
    start_receive();
}

void ClientUDP::send(const string& message) {
    socket_.send_to(asio::buffer(message), server_endpoint_);
}

void ClientUDP::start_receive() {
    socket_.async_receive_from(
        asio::buffer(recv_buffer_), server_endpoint_,
        [this](const system::error_code& error, size_t bytes_received) {
            handle_receive(error, bytes_received);
        });
}

void ClientUDP::handle_receive(const system::error_code& error, size_t bytes_received) {
    if (!error || error == asio::error::message_size) {
        std::lock_guard<std::mutex> lock(mutex_);
        memcpy(&payload_, recv_buffer_.data(), sizeof(Payload));
    }
    start_receive();
}

void ClientUDP::stop() {
    stop_requested_ = true;
}

Payload ClientUDP::get_payload() {
    lock_guard<mutex> lock(mutex_);
    return payload_;
}

ClientUDP::~ClientUDP() {};