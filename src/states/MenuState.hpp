#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <engine/State.hpp>
#include <engine/TextMenu.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class MenuState : public State
{
public:
  explicit     MenuState( StateStack& stack );
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

  sf::Sprite mBackgroundSprite;
  sf::Text   mTitle;
  TextMenu   mMenu;
};

#endif