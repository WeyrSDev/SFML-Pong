#ifndef CORE_TEXTMENU_HPP
#define CORE_TEXTMENU_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

// forward declarations for pimpl
namespace sf
{
  class Font;
  class Event;
  class Time;
  class String;
}

namespace core
{
// Class for a complete but simple to use text menu
// returns selected menu index when Return is pressed
// or -1 of Return has not been pressed
class TextMenu : public sf::Drawable, public sf::Transformable
{
public:
  // enum for aligning the text menu entries
  enum class Alignment
  {
    LEFT,
    CENTER,
    RIGHT,
  };

  // Contructs a new instance with a given font, text size, text spacing
  // default Alignment center, base color white, highlight color red
  // only saves a reference to a font, so font must live for the life time
  // of a TextMenu instance
  TextMenu( sf::Font& font, unsigned int textSize, unsigned int space,
            sf::Event::EventType keyEventType,
            Alignment alignment = Alignment::CENTER,
            sf::Color baseColor = sf::Color::White,
            sf::Color highlightColor = sf::Color::Red );

  // explicit default deconstructor needed cause of unique_ptr member
  ~TextMenu();

  // handles changing between different menu entries
  // returns selected menu index or -1 if nothing was selected
  int             handleInput( const sf::Event& event );

  // can be used for fancy menu effects
  // does nothing by default
  void            update( sf::Time dt );

  // adds a new entry to the menu, order does matter
  void            add( sf::String entry );

  // getters and setters for various members
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

  // SFML-like Bounding Rectangle calculations
  sf::FloatRect   getLocalBounds() const;
  sf::FloatRect   getGlobalBounds() const;

private:
  // override of sf::Drawable::draw()
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  // forward declaration of private class
  class Impl;
  // unique_ptr to private implementation
  std::unique_ptr<Impl> mImpl;

  // delete copy constructor
  TextMenu( const TextMenu& ) = delete;
  // delete copy assignment operator
  TextMenu& operator=( const TextMenu& ) = delete;
};

} // end namespace core
#endif