#ifndef CORE_UTILITY_HPP
#define CORE_UTILITY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include <type_traits>
#include <fstream>
#include <iostream>
#include <string>

// provides utility functions and classes
namespace core {
static const float PI = 3.1415962f;

// create a random int between min and max (inclusive)
int randomInt(int min, int max);

// converts radians to degrees
float radToDeg(float radian);

// converts degrees to radians
float degToRad(float degree);

// calculates length of a vector
float length(sf::Vector2f vector);

// normalizes a vector to length=1, also called unit vector
sf::Vector2f normalizeVector(sf::Vector2f vector);

// convert a polar angle to a 2D vector, angle must be in radians
sf::Vector2f toVector(float angle);

// normalize an angle to be always between 0 and 360 degree
int normalizeAngle(int angle);

// center the origin of a SFML entity to its center
template<typename T>
void centerOrigin(T &t);

// converts any enum class variable to its underlying type
// constexpr supported and required in VS2015 and GCC >4.9.1
template<typename T>
constexpr auto to_integral(T t) -> typename std::underlying_type<T>::type;

// get a string representation of the given event type
std::string eventToString(sf::Event::EventType type);

// take a screenshot of the given RenderWindow instance and
// save it to file asynchronously using C++11 threads
void makeScreenshot(const sf::RenderWindow &window, std::string filePrefix);

// return position (as upper left corner) of an sf::Rect as sf::Vector for convenience
template<typename T>
sf::Vector2<T> getPosition(const sf::Rect<T> &rectangle);

// return size of an sf::Rect as sf::Vector for convenience
template<typename T>
sf::Vector2<T> getSize(const sf::Rect<T> &rectangle);

// return a string representation of a sf::Rect<t> for debug purposes
template<typename T>
std::string to_string(const sf::Rect<T> &rectangle);

// return a string representation of a game entity for debug purposes
template<typename T>
std::string dumpToString(const T &t);

// return a string rep of a float fixed to given number of digits
// digits defaults to 1 and is limited between 0 and 10
std::string floatToString(float value, unsigned int digits = 1u);

// return a string representation of current day and time
// defaults to human readably dd-mm-yy HH:MM:SS format
// parameter needs to be const char* because of deprecated implicit conversion
std::string getDayTime(const char *format = "%d-%m-%y %H:%M:%S");

#include "Utility.inl"

} // core

#endif // CORE_UTILITY_HPP