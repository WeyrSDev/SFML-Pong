#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include <engine/State.hpp>
#include <engine/TextMenu.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameoverState : public core::State
{
public:
               GameoverState( core::StateStack& stack, States id );
  virtual bool handleInput( const sf::Event& event ) override;
  virtual bool update( sf::Time dt ) override;
  virtual void render() override;

private:
  enum class MenuOption : unsigned int
  {
    PLAY = 0u,
    MENU = 1u,
    EXIT = 2u,
  };

  sf::Sprite mBackgroundSprite;
  sf::Text mGameoverText;
  core::TextMenu mMenu;
};

#endif