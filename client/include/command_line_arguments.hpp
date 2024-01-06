#if !defined(COMMAND_LINE_ARGUMENTS_HPP)
#    define COMMAND_LINE_ARGUMENTS_HPP

#    include <cstdlib>
#    include <iostream>
#    include <string>

class CommandLineArgs {
public:
    std::string ip_address;
    int port;

    CommandLineArgs() : ip_address("127.0.0.1"), port(12345) {}

    bool parse_command_line_arguments(int argc, char* argv[]);

private:
    void show_usage(const std::string& program_name);
};

#endif  // COMMAND_LINE_ARGUMENTS_HPP
