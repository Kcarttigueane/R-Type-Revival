/**
 * @file command_line_arguments.hpp
 * @brief Defines the CommandLineArgs class for parsing command line arguments.
 */

#ifndef COMMAND_LINE_ARGUMENTS_HPP
#define COMMAND_LINE_ARGUMENTS_HPP

#include <cstdlib>
#include <iostream>
#include <string>

/**
 * @class CommandLineArgs
 * @brief A class to parse and store command line arguments.
 *
 * This class parses command line arguments and stores the IP address and port number.
 */
class CommandLineArgs {
public:
    std::string _ip_address;  ///< The IP address to connect to.
    int _port;                ///< The port number to connect to.

    /**
     * @brief Default constructor.
     *
     * Initializes the IP address to "127.0.0.1" and the port number to 5000.
     */
    CommandLineArgs() : _ip_address("127.0.0.1"), _port(5000) {}

    /**
     * @brief Parses command line arguments.
     *
     * @param argc The number of command line arguments.
     * @param argv The command line arguments.
     * @return true if the arguments were parsed successfully, false otherwise.
     */
    bool parse_command_line_arguments(int argc, char* argv[])
    {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-h" || arg == "--help") {
                show_usage(argv[0]);
                return false;
            }
        }

        if (argc != 3) {
            show_usage(argv[0]);
            return false;
        }

        if (argc == 3) {
            try {
                _ip_address = argv[1];
                _port = std::stoi(argv[2]);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid port number: " << argv[2] << std::endl;
                show_usage(argv[0]);
                return false;
            } catch (const std::out_of_range& e) {
                std::cerr << "Port number out of range: " << argv[2] << std::endl;
                show_usage(argv[0]);
                return false;
            }
        }

        return true;
    }

private:
    /**
     * @brief Displays usage information.
     *
     * @param program_name The name of the program.
     */
    void show_usage(const std::string& program_name)
    {
        std::cout << "Usage: " << program_name << " [<IP address> <port>]" << std::endl;
        std::cout << "Example: " << program_name << " 127.0.0.1 5000" << std::endl;
        std::cout << "If no IP address and port are provided, defaults to " << _ip_address << " "
                  << _port << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << " -h, --help\tShow this help message" << std::endl;
    }
};

#endif  // COMMAND_LINE_ARGUMENTS_HPP
