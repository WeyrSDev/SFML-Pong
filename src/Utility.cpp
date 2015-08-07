#include <pong/Utility.hpp>
#include <ctime>
#include <random>
#include <cassert>

namespace util
{

  namespace // anonymous namespace to hide its contents outside this translation unit
  {
    std::mt19937 createRandomEngine()
    {
      auto seed = static_cast<unsigned long>( std::time( nullptr ) );
      return std::mt19937( seed );
    }

    auto RandomEngine = createRandomEngine();

    const float PI = 4.f * std::atan( 1.f );
  }

  int randomInt( const int min, const int max )
  {
    std::uniform_int_distribution<int> dist( min, max );
    return dist( RandomEngine );
  }

  float radToDeg( const float radian )
  {
    return 180.f / PI * radian;
  }

  float degToRad( const float degree )
  {
    return PI / 180.f * degree;
  }

  float length( const sf::Vector2f vector )
  {
    return std::sqrt( vector.x * vector.x + vector.y * vector.y );
  }

  sf::Vector2f normalize( const sf::Vector2f vector )
  {
    assert( vector != sf::Vector2f( 0.f, 0.f ) );
    return vector / length( vector );
  }

  sf::Vector2f toVector( const float angle )
  {
    sf::Vector2f vector = { std::cos( angle ), std::sin( angle ) };
    return vector;
  }

} // end namespace util