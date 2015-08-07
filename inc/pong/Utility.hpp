#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>


namespace util
{
  // create a random int between min and max (inclusive)
  int randomInt( int min, int max );

  // center the origin of a SFML entity to its center
  template<typename T>
  void centerOrigin( T& t );

  // converts radians to degrees
  float radToDeg( float radian );

  // converts degrees to radians
  float degToRad( float degree );

  // calculates length of a vector
  float length( sf::Vector2f vector );

  // normalizes a vector to length=1, also called unit vector
  sf::Vector2f normalize( sf::Vector2f vector );

  // convert a polar angle to a 2D vector, angle must be in radians
  sf::Vector2f toVector( float angle );



#include "Utility.inl"

} // end namespace util
#endif