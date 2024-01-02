#include <iostream>
#include <string>

struct ParsedArgs {
    std::string ip_address;
    int port;
    bool success;

    ParsedArgs() : ip_address(""), port(0), success(false) {}
};

ParsedArgs parse_arguments(int argc, char* argv[])
{
    ParsedArgs args;

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP address> <port>"
                  << std::endl;
        args.success = false;
        return args;
    }

    args.ip_address = argv[1];

    try {
        args.port = std::stoi(argv[2]);
        args.success = true;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid port number: " << argv[2] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Port number out of range: " << argv[2] << std::endl;
    }

    return args;
}
