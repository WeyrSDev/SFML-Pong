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
    throw std::runtime_error( "[FATAL]\tCannot open log file " + mFileName );
  }
  std::string header { "[INFO]\tStarting up log system\n" };
  header += "[INFO]\tLog level set to " + std::to_string( to_integral( mLogLevel ) );
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
  switch( logType ) {
    case LogType::INFO:
      val = "[INFO]\t";
      break;

    case LogType::DEBUG:
      val = "[DEBUG]\t";
      break;

    case LogType::WARNING:
      val = "[WARNING]\t";
      break;

    case LogType::ERROR:
      val = "[ERROR]\t";
      break;

    case LogType::FATAL:
      val = "[FATAL]\t";
      break;

    case LogType::NONE:
      break;
  }
  val += getDayTime( "%H:%M:%S\t" );
  val += msg;
  mLogFile << val << std::endl;
  *mOpStr << val << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

} // end namespace core