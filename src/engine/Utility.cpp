#include "Utility.hpp"
#include <SFML/Graphics/Texture.hpp>
//#include <ctime>
#include <random>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <chrono>

#if defined(_WIN32) && defined(_MSC_VER)
#include <thread>
#define STD_THREAD 1
#elif defined(_WIN32) && defined(__MINGW32__)
// here needs to be an include for mingw posix thread implementation
#elif defined(__LINUX__)
#include <thread>
#define STD_THREAD 1
#endif

namespace core
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

} // end anonymous namespace

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
  // TODO: Remove unnecessary temporary
  sf::Vector2f vector = { std::cos( angle ), std::sin( angle ) };
  return vector;
}

///////////////////////////////////////////////////////////////////////////////

int normalizeAngle( int angle )
{
  // TODO: Remove unnecessary temporary
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

std::string eventToString( sf::Event::EventType type )
{
  // Macro for easier definition of switch statement
#define EVENTTOSTRING_CASE(TYPE) case sf::Event::EventType::TYPE: return #TYPE;

  switch( type ) {
    EVENTTOSTRING_CASE( Closed )
    EVENTTOSTRING_CASE( Resized )
    EVENTTOSTRING_CASE( LostFocus )
    EVENTTOSTRING_CASE( GainedFocus )
    EVENTTOSTRING_CASE( TextEntered )
    EVENTTOSTRING_CASE( KeyPressed )
    EVENTTOSTRING_CASE( KeyReleased )
    EVENTTOSTRING_CASE( MouseWheelMoved )
    EVENTTOSTRING_CASE( MouseWheelScrolled )
    EVENTTOSTRING_CASE( MouseButtonPressed )
    EVENTTOSTRING_CASE( MouseButtonReleased )
    EVENTTOSTRING_CASE( MouseMoved )
    EVENTTOSTRING_CASE( MouseEntered )
    EVENTTOSTRING_CASE( MouseLeft )
    EVENTTOSTRING_CASE( JoystickButtonPressed )
    EVENTTOSTRING_CASE( JoystickButtonReleased )
    EVENTTOSTRING_CASE( JoystickMoved )
    EVENTTOSTRING_CASE( JoystickConnected )
    EVENTTOSTRING_CASE( JoystickDisconnected )
    EVENTTOSTRING_CASE( TouchBegan )
    EVENTTOSTRING_CASE( TouchMoved )
    EVENTTOSTRING_CASE( TouchEnded )
    EVENTTOSTRING_CASE( SensorChanged )
  }
  return std::string { "UNKNOWN" };
}

///////////////////////////////////////////////////////////////////////////////

void makeScreenshot( const sf::RenderWindow& window, std::string filePrefix )
{
  // create a texture with the size of the current window
  const auto size = window.getSize();
  sf::Texture screenshot;
  screenshot.create( size.x, size.y );

  // create the screenshot from the current screen buffer
  screenshot.update( window );
  sf::Image img = screenshot.copyToImage();

  // set the filename with prefix current date and time
  // if prefix is empty use generic engine name
  // Remember to not use : or other forbidden characters in format string
  // Also note that getDayTime is not thread-safe
  // and should be used in main thread only
  if( filePrefix == "" ) {
    filePrefix = "core";
  }
  std::string filename = filePrefix + getDayTime( "-%d%m%y-%H%M%S" ) + ".png";

  // save it to file in another thread for no performance hit in main thread
  #ifdef STD_THREAD
  std::thread t( [ img,filename ]() { img.saveToFile( filename ); } );
  t.detach();
  #else
  img.saveToFile( filename );
  #endif
}

///////////////////////////////////////////////////////////////////////////////

std::string floatToString( float value, unsigned int digits )
{
  if( digits > 10u ){
    digits = 10u;
  }

  std::stringstream sstream;
  sstream << std::fixed << std::setprecision( digits ) << value;
  return sstream.str();
}

///////////////////////////////////////////////////////////////////////////////

std::string getDayTime( const char* format )
{
  // this function uses plain old C in combination with C++11 std::chrono
  // TODO: should be replaced with something based on Hinnants C++ Date lib
  // atm date.h isn't fully supported by VS2015 so fallback to C here ;)
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t( now );

  // one can safely ignore VS complaining about std::localtime being deprecated
  // you can disable this warning in the project settings in VS on file level
  // it is ISO C++ conformant BUT remember it is NOT thread safe
  std::stringstream sstream;  
  sstream << std::put_time( std::localtime( &in_time_t ), format );
  return sstream.str();
}

///////////////////////////////////////////////////////////////////////////////

} // end namespace core