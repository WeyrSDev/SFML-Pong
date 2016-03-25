#ifndef CORE_FPSDISPLAY_HPP
#define CORE_FPSDISPLAY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>

// forward declarations for pimpl
namespace sf
{
  class Font;
  class Text;
  class Time;
}

namespace core
{
// Simple framerate display for SFML applications
// stores only a reference of sf::Font, so font must
// be alive for the life time of FpsDisplay
class FpsDisplay : public sf::Drawable, public sf::Transformable
{
public:
  // Contructs a new instance of FpsDisplay with a given font
  // size defaults to 12 pixel
  FpsDisplay( const sf::Font& font, unsigned int size = 12u );

  // explicit default deconstructor needed cause of unique_ptr-member
  ~FpsDisplay();

  // update with a valid sf::Time object
  // needs to be called every frame of the sfml window
  void update( sf::Time dt );

private:
  // override of sf::Drawable::draw()
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  // forward definition of private implementation class
  class Impl;

  // unique_ptr to private implementation
  std::unique_ptr<Impl> mImpl;

  // delete copy constructor
  FpsDisplay( const FpsDisplay& ) = delete;

  // delete copy assignment operator
  FpsDisplay& operator=( const FpsDisplay& ) = delete;
};

} // end namespace core
#endif