#include "Utility.hpp"
#include <ctime>
#include <random>
#include <cassert>

namespace util
{
///////////////////////////////////////////////////////////////////////////////
  namespace // anonymous namespace to hide its contents outside this TU
  {
    std::mt19937 createRandomEngine()
    {
      auto seed = static_cast<unsigned long>( std::time( nullptr ) );
      return std::mt19937( seed );
    }

    auto RandomEngine = createRandomEngine();

    const float PI = 4.f * std::atan( 1.f );
  }

///////////////////////////////////////////////////////////////////////////////

  int randomInt( const int min, const int max )
  {
    std::uniform_int_distribution<int> dist( min, max );
    return dist( RandomEngine );
  }

///////////////////////////////////////////////////////////////////////////////

  float radToDeg( const float radian )
  {
    return 180.f / PI * radian;
  }

///////////////////////////////////////////////////////////////////////////////

  float degToRad( const float degree )
  {
    return PI / 180.f * degree;
  }

///////////////////////////////////////////////////////////////////////////////

  float length( const sf::Vector2f vector )
  {
    return std::sqrt( vector.x * vector.x + vector.y * vector.y );
  }

///////////////////////////////////////////////////////////////////////////////

  sf::Vector2f normalizeVector( const sf::Vector2f vector )
  {
    assert( vector != sf::Vector2f( 0.f, 0.f ) );
    return vector / length( vector );
  }

///////////////////////////////////////////////////////////////////////////////

  sf::Vector2f toVector( const float angle )
  {
    sf::Vector2f vector = { std::cos( angle ), std::sin( angle ) };
    return vector;
  }

///////////////////////////////////////////////////////////////////////////////

  int normalizeAngle( int angle )
  {
    auto temp = angle;
    while( temp > 360 ) {
      temp -= 360;
    }

    while( temp < 0 ) {
      temp += 360;
    }

    return temp;
  }  

///////////////////////////////////////////////////////////////////////////////

  Log::Log( std::string logfile, LogType logLevel, std::ostream* opStr )
    : mFileName( logfile )
    , mLogFile( mFileName )
    , mOpStr( opStr )
    , mLogLevel( logLevel )
  {
    if( !mLogFile ) {
      throw std::runtime_error( "FATAL: Cannot open log file " + mFileName );
    }

    std::cout << "[INFO] Log level set to "
      << std::to_string( to_integral( mLogLevel ) ) << std::endl;
  }

///////////////////////////////////////////////////////////////////////////////

  void Log::msg( sf::String msg, LogType logType )
  {
    if( logType > mLogLevel ) {
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
    }

    val += msg;
    mLogFile << val << std::endl;
    *mOpStr << val << std::endl;
  }

///////////////////////////////////////////////////////////////////////////////

  std::string eventToString( sf::Event::EventType type )
  {
    // Macro for easier definition of switch statement
#define EVENTTOSTRING_CASE(TYPE) case sf::Event::EventType::TYPE: return #TYPE;

    switch( type ) {
      EVENTTOSTRING_CASE(Closed)
      EVENTTOSTRING_CASE(Resized)
      EVENTTOSTRING_CASE(LostFocus)
      EVENTTOSTRING_CASE(GainedFocus)
      EVENTTOSTRING_CASE(TextEntered)
      EVENTTOSTRING_CASE(KeyPressed)
      EVENTTOSTRING_CASE(KeyReleased)
      EVENTTOSTRING_CASE(MouseWheelMoved)
      EVENTTOSTRING_CASE(MouseWheelScrolled)
      EVENTTOSTRING_CASE(MouseButtonPressed)
      EVENTTOSTRING_CASE(MouseButtonReleased)
      EVENTTOSTRING_CASE(MouseMoved)
      EVENTTOSTRING_CASE(MouseEntered)
      EVENTTOSTRING_CASE(MouseLeft)
      EVENTTOSTRING_CASE(JoystickButtonPressed)
      EVENTTOSTRING_CASE(JoystickButtonReleased)
      EVENTTOSTRING_CASE(JoystickMoved)
      EVENTTOSTRING_CASE(JoystickConnected)
      EVENTTOSTRING_CASE(JoystickDisconnected)
      EVENTTOSTRING_CASE(TouchBegan)
      EVENTTOSTRING_CASE(TouchMoved)
      EVENTTOSTRING_CASE(TouchEnded)
      EVENTTOSTRING_CASE(SensorChanged)
    }
    return std::string{ "UNKNOWN" };
  }

///////////////////////////////////////////////////////////////////////////////

} // end namespace util