#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <type_traits>
#include <fstream>
#include <iostream>

// provides utility functions and classes
namespace util
{
  // create a random int between min and max (inclusive)
  int randomInt( int min, int max );

  // converts radians to degrees
  float radToDeg( float radian );

  // converts degrees to radians
  float degToRad( float degree );

  // calculates length of a vector
  float length( sf::Vector2f vector );

  // normalizes a vector to length=1, also called unit vector
  sf::Vector2f normalizeVector( sf::Vector2f vector );

  // convert a polar angle to a 2D vector, angle must be in radians
  sf::Vector2f toVector( float angle );

  // normalize an angle to be always between 0 and 360 degree
  int normalizeAngle( int angle );

  // center the origin of a SFML entity to its center
  template<typename T>
  void centerOrigin( T& t );

  // converts any enum class variable to its underlying type
  // constexpr supported and required in VS2015 and GCC >4.9.1
  template<typename T>
  constexpr auto to_integral( T t ) -> typename std::underlying_type<T>::type;

  // enumeration used to determine type of log message
  // also used for height of log level, the higher the more verbose
  enum class LogType : unsigned int
  {
    NONE = 0u,
    ERROR = 1u,
    WARNING = 2u,
    INFO = 3u,
    DEBUG = 4u,
  };

  class Log
  {
  public:
    explicit Log( std::string logfile, LogType logLevel = LogType::ERROR,
                  std::ostream* opStr = &std::cout );

    void msg( sf::String msg, LogType type = LogType::ERROR );

  private:
    std::string mFileName;
    std::ofstream mLogFile;
    std::ostream* mOpStr;
    LogType mLogLevel;


    Log( const Log& ) = delete;
    Log& operator=( const Log& ) = delete;
  };

  // get a string representation of the given event type
  std::string eventToString( sf::Event::EventType type );


#include "Utility.inl"

} // end namespace util
#endif