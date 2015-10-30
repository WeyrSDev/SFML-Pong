#ifndef FPSDISPLAY_HPP
#define FPSDISPLAY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

class FpsDisplay : public sf::Drawable, public sf::Transformable
{
public:
               FpsDisplay( );
  void         update( sf::Time dt );

private:
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  sf::Font     mFont;
  sf::Text     mFpsText;
  std::size_t  mFrames;
  std::size_t  mFps;
  sf::Time     mFpsTime;
};

#endif