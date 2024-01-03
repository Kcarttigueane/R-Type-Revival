#if !defined(COMMAND_LINE_ARGUMENTS_HPP)
#    define COMMAND_LINE_ARGUMENTS_HPP

#    include <cstdlib>
#    include <iostream>
#    include <string>

class CommandLineArgs {
public:
    std::string ip_address;
    int port;

    CommandLineArgs() : ip_address("127.0.0.1"), port(5000) {}

    bool parse(int argc, char* argv[])
    {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-h" || arg == "--help") {
                show_usage(argv[0]);
                return false;
            }
        }

        if (argc > 3) {
            std::cerr << "Too many arguments." << std::endl;
            show_usage(argv[0]);
            return false;
        }

        if (argc >= 2) {
            ip_address = argv[1];
        }

        if (argc == 3) {
            try {
                port = std::stoi(argv[2]);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid port number: " << argv[2] << std::endl;
                show_usage(argv[0]);
                return false;
            } catch (const std::out_of_range& e) {
                std::cerr << "Port number out of range: " << argv[2]
                          << std::endl;
                show_usage(argv[0]);
                return false;
            }
        }

        return true;
    }

private:
    void show_usage(const std::string& program_name)
    {
        std::cout << "Usage: " << program_name << " [<IP address> <port>]"
                  << std::endl;
        std::cout << "Example: " << program_name << " 127.0.0.1 5000"
                  << std::endl;
        std::cout << "If no IP address and port are provided, defaults to "
                  << ip_address << " " << port << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << " -h, --help\tShow this help message" << std::endl;
    }
};

#endif  // COMMAND_LINE_ARGUMENTS_HPP