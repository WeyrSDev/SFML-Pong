#ifndef FPSDISPLAY_HPP
#define FPSDISPLAY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

class FpsDisplay : public sf::Drawable, public sf::Transformable
{
public:
               FpsDisplay( const sf::Font& font, unsigned int size = 12u );
  void         update( sf::Time dt );

private:
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  class Impl;
  std::unique_ptr<Impl> mImpl;

  FpsDisplay( const FpsDisplay& ) = delete;
  FpsDisplay& operator=( const FpsDisplay& ) = delete;
};

#endif