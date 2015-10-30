#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <type_traits>

// provides utility functions
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
// should be constexpr but not supported in VC2013, only GCC >4.8.2
// constexpr supported and required in VS2015 and GCC >4.9.1
template<typename T>
constexpr auto to_integral( T t ) -> typename std::underlying_type<T>::type;

#include "Utility.inl"

} // end namespace util
#endif