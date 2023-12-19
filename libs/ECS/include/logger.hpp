#include <iostream>
#include <sstream>
#include <string>

class Logger {
public:
  enum class Level { INFO, WARNING, ERROR };

private:
  Level logLevel = Level::INFO;

public:
  void setLevel(Level newLevel) { logLevel = newLevel; }

  void log(const std::string &message, Level level) {
    if (level >= logLevel) {
      std::cout << "[" << levelToString(level) << "] " << message << std::endl;
    }
  }

  template <typename... Args> void log(Level level, Args... args) {
    if (level >= logLevel) {
      std::ostringstream ss;
      (ss << ... << args);
      log(ss.str(), level);
    }
  }

private:
  std::string levelToString(Level level) {
    switch (level) {
    case Level::INFO:
      return "INFO";
    case Level::WARNING:
      return "WARNING";
    case Level::ERROR:
      return "ERROR";
    default:
      return "UNKNOWN";
    }
  }
};

// Global logger instance
Logger logger;
