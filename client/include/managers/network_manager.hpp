// #if !defined(NETWORK_MANAGER_HPP)
// #    define NETWORK_MANAGER_HPP

// #    include <boost/array.hpp>
// #    include <boost/asio.hpp>
// #    include <boost/bind/bind.hpp>
// #    include <iostream>
// #    include <queue>
// #    include <thread>

// #    include "../../../build/common/proto/r_type.pb.h"
// #    include "../../../common/utils/id_generator.hpp"

// #    include "../config.hpp"

// #    include "../utils.hpp"

// using boost::asio::ip::udp;

// /**
//  * @file network_manager.hpp
//  * @brief Defines the NetworkManagerAsyncUDPClient class.
//  */

// /**
//  * @class NetworkManagerAsyncUDPClient
//  * @brief This class is responsible for managing network operations for the client.
//  *
//  * It uses the Boost.Asio library to perform asynchronous network operations over UDP.
//  * It also uses Google's Protocol Buffers for serializing structured data.
//  */
// class NetworkManagerAsyncUDPClient {
// private:
//     boost::asio::io_service& io_service_;

//     udp::socket socket_;
//     udp::endpoint server_endpoint_;
//     udp::endpoint remote_endpoint_;

//     std::array<char, BUFFER_SIZE> recv_buffer_;

//     std::queue<rtype::Payload> received_messages_;
//     std::mutex received_messages_mutex_;

//     std::mutex mutex_;

// public:
//     /**
//      * @brief Constructs a new NetworkManagerAsyncUDPClient.
//      *
//      * @param io_service The I/O service to use for network operations.
//      * @param host The host to connect to.
//      * @param port The port to connect to.
//      */
//     NetworkManagerAsyncUDPClient(
//         boost::asio::io_service& io_service, const std::string& host, const std::string& port
//     )
//         : io_service_(io_service), socket_(io_service, udp::endpoint(udp::v4(), 0))
//     {
//         udp::resolver resolver(io_service_);
//         udp::resolver::query query(udp::v4(), host, port);
//         udp::resolver::iterator iter = resolver.resolve(query);
//         server_endpoint_ = *iter;
//         receive();
//     }

//     /**
//      * @brief Destroys the NetworkManagerAsyncUDPClient.
//      */
//     ~NetworkManagerAsyncUDPClient() { socket_.close(); }

//     /**
//      * @brief Sends a payload to the server.
//      *
//      * @param payload The payload to send.
//      */
//     void send(const rtype::Payload& payload);

//     /**
//      * @brief Starts an asynchronous receive operation.
//      */
//     void receive();

//     /**
//      * @brief Handles the completion of a receive operation.
//      *
//      * @param error The error code, if any.
//      * @param bytes_transferred The number of bytes received.
//      */
//     void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);

//     /**
//      * @brief Processes a received payload.
//      *
//      * @param payload The payload to process.
//      */
//     void processPayload(const rtype::Payload& payload);

//     /**
//      * @brief Handles a connect response payload.
//      *
//      * @param payload The payload to handle.
//      */
//     void handleConnectResponse(const rtype::Payload& payload);

//     /**
//      * @brief Handles a game state payload.
//      *
//      * @param payload The payload to handle.
//      */
//     void handleGameState(const rtype::Payload& payload);

//     /**
//      * @brief Returns the received messages.
//      *
//      * @return A queue of received payloads.
//      */
//     std::queue<rtype::Payload> getReceivedMessages();
// };

// #endif  // NETWORK_MANAGER_HPP
