
template<typename T>
void centerOrigin( T& t )
{
  auto bounds = t.getLocalBounds();
  float x = std::floor( bounds.left + bounds.width / 2.f );
  float y = std::floor( bounds.top + bounds.height / 2.f );
  t.setOrigin( x, y );
}
