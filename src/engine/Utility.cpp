#include "Utility.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <ctime>
#include <random>
#include <cassert>
#include <thread>

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

void makeScreenshot( const sf::RenderWindow& window )
{
  // create a texture with the size of the current window
  const auto size = window.getSize();
  sf::Texture screenshot;
  screenshot.create( size.x, size.y );

  // create the screenshot from the current screen buffer
  screenshot.update( window );
  sf::Image img = screenshot.copyToImage();

  // save it to file in another thread for no performance hit in main thread
  std::thread t( [ img ]() { img.saveToFile( "screenshot.png" ); } );
  t.detach();
}

///////////////////////////////////////////////////////////////////////////////

std::string dumpToString( const sf::Sprite& sprite )
{
  const auto position = sprite.getPosition();
  const auto origin = sprite.getOrigin();
  const auto lBounds = sprite.getLocalBounds();
  const auto gBounds = sprite.getGlobalBounds();

  std::string spriteString = "\tpos.x=" + std::to_string( position.x ) + " " +
    "\tpos.y=" + std::to_string( position.y ) + "\n" + 
    "\torg.x=" + std::to_string( origin.x ) + " " +
    "\torg.y=" + std::to_string( origin.y ) + "\n" +
    "\tlBounds:" + to_string( lBounds ) + "\n" +
    "\tgBounds:" + to_string( gBounds );

  return spriteString;
}

///////////////////////////////////////////////////////////////////////////////

} // end namespace core