#ifndef TEXTMENU_HPP
#define TEXTMENU_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <memory>

namespace sf
{
  class Font;
  class Event;
  class Time;
  class String;
}

class TextMenu : public sf::Drawable, public sf::Transformable
{
public:
  enum class Alignment
  {
    LEFT,
    CENTER,
    RIGHT,
  };

  TextMenu( sf::Font& font, unsigned int textSize, unsigned int space,
            Alignment alignment = Alignment::CENTER,
            sf::Color baseColor = sf::Color::White,
            sf::Color highlightColor = sf::Color::Red );

  ~TextMenu();

  // returns selected menu entry when return is pressed
  // or -1 if return was not pressed
  int             handleInput( const sf::Event& event );
  void            update( sf::Time dt );
  void            add( sf::String entry );

  void            setTextSize( unsigned int size );
  unsigned int    getTextSize() const;
  void            setSpacing( unsigned int space );
  unsigned int    getSpacing() const;
  void            setAlignment( Alignment alignment );
  Alignment       getAlignment() const;
  void            setBaseColor( sf::Color base );
  sf::Color       getBaseColor() const;
  void            setHighlightColor( sf::Color highlight );
  sf::Color       getHighlightColor() const;
  sf::FloatRect   getLocalBounds() const;
  sf::FloatRect   getGlobalBounds() const;

private:
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) 
    const override;

  class Impl;
  std::unique_ptr<Impl> mImpl;

  TextMenu( const TextMenu& ) = delete;
  TextMenu& operator=( const TextMenu& ) = delete;
};

#endif