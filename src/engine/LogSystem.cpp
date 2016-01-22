#include "LogSystem.hpp"
#include "Utility.hpp"

namespace core
{
///////////////////////////////////////////////////////////////////////////////

LogSystem::LogSystem( std::string logfile, LogType logLevel, std::ostream* opStr )
  : mFileName( logfile )
  , mLogFile( mFileName )
  , mOpStr( opStr )
  , mLogLevel( logLevel )
{
  if( !mLogFile ) {
    throw std::runtime_error( "[FATAL] Cannot open log file " + mFileName );
  }
  std::string header { "[INFO] Starting up log system\n" };
  header += "[INFO] Log level set to " + std::to_string( to_integral( mLogLevel ) );
  mLogFile << header << std::endl;
  *mOpStr << header << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

void LogSystem::write( sf::String msg, LogType logType )
{
  if( logType > mLogLevel || mLogLevel == LogType::NONE ) {
    return;
  }

  std::string val;
  // TODO: add timestamp to val
  switch( logType ) {
    case LogType::INFO:
      val = "[INFO] ";
      break;

    case LogType::DEBUG:
      val = "[DEBUG] ";
      break;

    case LogType::WARNING:
      val = "[WARNING] ";
      break;

    case LogType::ERROR:
      val = "[ERROR] ";
      break;

    case LogType::FATAL:
      val = "[FATAL] ";
      break;
  }

  val += msg;
  mLogFile << val << std::endl;
  *mOpStr << val << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

} // end namespace core