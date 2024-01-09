#if !defined(NETWORK_MANAGER_HPP)
#    define NETWORK_MANAGER_HPP

#    include <boost/array.hpp>
#    include <boost/asio.hpp>
#    include <iostream>
#    include <thread>

#    include "../../../build/common/proto/payload.pb.h"

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
                                // std::cout << "Message : "
                                //           << message.ShortDebugString()
                                //           << std::endl;
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
            // std::cout << "First payload " << payload.ShortDebugString() << std::endl;
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
        // std::cout << "Send payload : " << event.ShortDebugString() << std::endl;
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

#endif  // NETWORK_MANAGER_HPP
