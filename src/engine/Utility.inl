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