#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include <engine/State.hpp>
#include <engine/TextMenu.hpp>

#include <memory>

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
    MENU,
    EXIT,
  };

  core::TextMenu mMenu;
  std::vector<std::unique_ptr<sf::Drawable>> mDrawObjects;
};

#endif