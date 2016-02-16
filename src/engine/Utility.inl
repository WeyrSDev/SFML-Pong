///////////////////////////////////////////////////////////////////////////////

template<typename T>
void centerOrigin( T& t )
{
  auto bounds = t.getLocalBounds();
  float x = std::floor( bounds.left + bounds.width / 2.f );
  float y = std::floor( bounds.top + bounds.height / 2.f );
  t.setOrigin( x, y );
}

///////////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr auto to_integral( T t ) -> typename std::underlying_type<T>::type
{
  return static_cast<typename std::underlying_type<T>::type>( t );
}

///////////////////////////////////////////////////////////////////////////////

template<typename T>
sf::Vector2<T> getPosition( const sf::Rect<T>& rectangle )
{
  return sf::Vector2<T>( rectangle.left, rectangle.top );
}

///////////////////////////////////////////////////////////////////////////////

template<typename T>
sf::Vector2<T> getSize( const sf::Rect<T>& rectangle )
{
  return sf::Vector2<T>( rectangle.width, rectangle.height );
}

///////////////////////////////////////////////////////////////////////////////

template<typename T>
std::string to_string( const sf::Rect<T>& rectangle )
{
  return std::string( "Left=" + std::to_string( rectangle.left ) + " "
                      + "Top=" + std::to_string( rectangle.top ) + " "
                      + "Width=" + std::to_string( rectangle.width ) + " "
                      + "Height=" + std::to_string( rectangle.height ) );
}

///////////////////////////////////////////////////////////////////////////////

template<typename T>
std::string dumpToString( const T& t )
{
  const auto position = t.getPosition();
  const auto origin = t.getOrigin();
  const auto lBounds = t.getLocalBounds();
  const auto gBounds = t.getGlobalBounds();

  std::string spriteString = "\tpos.x=" + std::to_string( position.x ) + " " +
    "pos.y=" + std::to_string( position.y ) + "\n" +
    "\torg.x=" + std::to_string( origin.x ) + " " +
    "org.y=" + std::to_string( origin.y ) + "\n" +
    "\tlBounds:" + to_string( lBounds ) + "\n" +
    "\tgBounds:" + to_string( gBounds );

  return spriteString;
}

///////////////////////////////////////////////////////////////////////////////