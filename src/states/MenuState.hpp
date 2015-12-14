#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <engine/State.hpp>
#include <engine/TextMenu.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>

class MenuState : public State
{
public:
               MenuState( StateStack& stack, States id );
  virtual bool handleInput( const sf::Event& event ) override;
  virtual bool update( sf::Time dt ) override;
  virtual void render() override;

private:
  enum class MenuOption : unsigned int
  {
    PLAY = 0u,
    OPTIONS = 1u,
    CREDITS = 2u,
    EXIT = 3u,
  };

  TextMenu   mMenu;
  std::vector<std::unique_ptr<sf::Drawable>> mDrawObjects;
};

#endif