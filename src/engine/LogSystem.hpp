#ifndef CORE_LOGSYSTEM_HPP
#define CORE_LOGSYSTEM_HPP
#include <SFML/System/String.hpp>
#include <string>
#include <iostream>
#include <fstream>

namespace core
{
// enumeration used to determine type of log message
// also used for height of log level, the higher the more verbose
enum class LogType : unsigned int
{
  NONE = 0u,
  FATAL,
  ERROR,
  WARNING,
  INFO,
  DEBUG,
};

// This class provides a simple log system with support for a log file and a
// user defined output stream. Log level defaults to LogType::ERROR,
// custom output stream defaults to std::cout
class LogSystem
{
public:
  explicit      LogSystem( std::string logfile, LogType logLevel = LogType::ERROR,
                           std::ostream* opStr = &std::cout );

  void          write( sf::String msg, LogType type = LogType::ERROR );

private:
  std::string   mFileName;
  std::ofstream mLogFile;
  std::ostream* mOpStr;
  LogType       mLogLevel;


  LogSystem( const LogSystem& ) = delete;
  LogSystem& operator=( const LogSystem& ) = delete;
};

} // end namespace core

#endif