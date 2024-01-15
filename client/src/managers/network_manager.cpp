#include "../../include/managers/network_manager.hpp"

void NetworkManagerAsyncUDPClient::send(const rtype::Payload& payload)
{
    std::string serialized_state;
    payload.SerializeToString(&serialized_state);

    socket_.async_send_to(
        boost::asio::buffer(serialized_state), server_endpoint_,
        [this](boost::system::error_code ec, std::size_t /*bytes_transferred*/) {
            if (ec) {
                std::cerr << "Send error: " << ec.message() << std::endl;
            }
        }
    );
}

void NetworkManagerAsyncUDPClient::receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(
            &NetworkManagerAsyncUDPClient::handle_receive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void NetworkManagerAsyncUDPClient::handle_receive(
    const boost::system::error_code& error, std::size_t bytes_transferred
)
{
    if (error) {
        std::cerr << "Receive error: " << error.message() << std::endl;
        return;
    }
    // std::cout << "udp::endpoint" << remote_endpoint_ << std::endl;
    // std::cout << "Remote endpoint: " << remote_endpoint_.address() << ":"
    //           << remote_endpoint_.port() << std::endl;

    std::string received_data(recv_buffer_.data(), bytes_transferred);
    rtype::Payload payload;

    if (payload.ParseFromString(received_data)) {
        processPayload(payload);
    } else {
        std::cerr << "Failed to parse received data as protobuf Payload message." << std::endl;
    }
    receive();
}

void NetworkManagerAsyncUDPClient::processPayload(const rtype::Payload& payload
)  // TODO : This should be in the game manager
{
    std::lock_guard<std::mutex> lock(received_messages_mutex_);

    std::cout << "Processing payload" << payload.DebugString() << std::endl;
    if (payload.has_connect_response()) {
        handleConnectResponse(payload);
    } else if (payload.has_game_state()) {
        handleGameState(payload);
    } else {
        std::cerr << "Unknown payload type received." << std::endl;
    }
}

void NetworkManagerAsyncUDPClient::handleConnectResponse(const rtype::Payload& payload)
{
    std::cout << CYAN << "Connect response received" << RESET << std::endl;
    received_messages_.push(payload);  // TODO : This should be pushed, I don't know
}

void NetworkManagerAsyncUDPClient::handleGameState(const rtype::Payload& payload)
{
    std::cout << CYAN << "Game state received" << RESET << std::endl;
    received_messages_.push(payload);
}

std::queue<rtype::Payload> NetworkManagerAsyncUDPClient::getReceivedMessages()
{
    std::lock_guard<std::mutex> lock(received_messages_mutex_);
    auto received_messages = std::move(received_messages_);

    while (!received_messages_.empty()) {
        received_messages_.pop();
    }

    return received_messages;
}
